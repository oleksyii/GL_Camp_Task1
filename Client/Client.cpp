/*
Packet stringPacket(PacketType::PT_ChatMessage);
stringPacket << std::string("App is running");

Packet integersPacket(PacketType::PT_IntegerArray);
uint32_t arraySize = 6;
uint32_t integerArray[6] = { 2, 5, 7, 1, 2, 9 };
integersPacket << arraySize;
for (auto integer : integerArray)
{
	integersPacket << integer;
}
*/
// Client code
#include <PNet/IncludeMe.h>
#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <atomic>
#include <mutex>
#include <locale>
#include <codecvt>
#include <map>

#ifndef _WIN32
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define Sleep(duration) usleep(duration * 1000)
#define GetLastError() errno
#endif // !_WIN32


using namespace PNet;

std::atomic<bool> appCeased(false);
std::mutex m_consoleAccess; // Mutex for console access
std::string appName = "";
std::mutex m_appNameAccess;

typedef struct MyData
{
	Socket *socket;
	MyData(Socket *ptr) : socket(ptr){};
} MYDATA, *PMYDATA;

std::mutex m_tableAccess;
std::map<std::string, bool> table;

bool presentInMap(std::map<std::string, bool> map, std::string value)
{
	std::lock_guard<std::mutex> lock(m_tableAccess);
	std::map<std::string, bool>::iterator it = map.find(value);
	return (it == map.end() ? false : true);
}

bool ProcessPacket(Packet &packet)
{
	switch (packet.GetPacketType())
	{
	case PacketType::PT_ChatMessage:
	{
		std::lock_guard<std::mutex> lock(m_appNameAccess);
		packet >> appName;
		std::cout << appName << std::endl;
		if (!presentInMap(table, appName))
		{
			std::lock_guard<std::mutex> lock(m_tableAccess);
			table.insert(std::pair<std::string, bool>(appName, true));
		}
		else if (table[appName])
		{
			std::lock_guard<std::mutex> lock(m_tableAccess);
			table[appName] = false;
		}
		else if (table[appName])
		{
			std::lock_guard<std::mutex> lock(m_tableAccess);
			table[appName] = true;
		}

		// TODO:
		// Remake the thing to be a dictionary to know whether app
		// should be stopped or not

		// std::string chatMessage;
		// packet >> chatMessage;
		// std::cout << "Chat Message: " << chatMessage << std::endl;
		break;
	}
	case PacketType::PT_IntegerArray:
	{
		uint32_t arraySize = 0;
		packet >> arraySize;
		std::cout << "Array size: " << arraySize << std::endl;
		for (uint32_t i = 0; i < arraySize; i++)
		{
			uint32_t element = 0;
			packet >> element;
			std::cout << "Element[" << i << "] - " << element << std::endl;
		}
		break;
	}
	default:
		return false;
	}
	return true;
}
/*
 * The fucntion's purpose is to get a name of the app to laucnh.
 * If the same name comes again it changes the atomic value to notify a thread to
 * force running app
 */
void HandleReceivingPackets(void *in)
{
	PMYDATA nn = static_cast<PMYDATA>(in);
	Socket socket = *(nn->socket);

	Packet packet;
	while (true)
	{
		PResult result = socket.Recv(packet);
		if (result != PResult::P_Success)
			break;

		if (!ProcessPacket(packet))
			break;
	}
	socket.Close();
}

void HandleSendingPackets(Socket &socket, Packet packet)
{
	PResult result;
	result = socket.Send(packet);

	if (result != PResult::P_Success)
		return;

	std::cout << "Attempting to send chunk of data..." << std::endl;
}

void HandleApp()
{
	bool proceed = false;
	{
		std::lock_guard<std::mutex> lock(m_tableAccess);
		std::lock_guard<std::mutex> lock2(m_appNameAccess);
		if (table[appName])
			proceed = true;
	}
#ifdef _WIN32
	if (proceed)
	{
		// Define the path to the application you want to launch
		// Convert the UTF-8 string to a UTF-16 wstrin
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring utf16String;
		{
			std::lock_guard<std::mutex> lock(m_appNameAccess);
			utf16String = converter.from_bytes(appName);
		}

		// CreateProcess parameters
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		// Launch the application
		if (!CreateProcess(
				NULL,										// Application name (use NULL to use command line)
				const_cast<wchar_t *>(utf16String.c_str()), // Command line
				NULL,										// Process security attributes
				NULL,										// Thread security attributes
				FALSE,										// Inherit handles
				0,											// Creation flags
				NULL,										// Use parent's environment
				NULL,										// Use parent's current directory
				&si,										// STARTUPINFO structure
				&pi											// PROCESS_INFORMATION structure
				))
		{
			std::cerr << "Error creating process: " << GetLastError() << std::endl;
			return;
			appCeased = true;
		}
		std::cout << "succesfully created app PID: " << pi.dwProcessId << "\nThreadID: " << pi.dwThreadId << std::endl;
		// Wait for the application to finish, checking every one second
		DWORD exitCode;
		while (true)
		{
			if (WaitForSingleObject(pi.hProcess, 1000) == WAIT_OBJECT_0 &&
				GetExitCodeProcess(pi.hProcess, &exitCode))
			{
				appCeased = true;
				std::cout << "Application exited with code: " << exitCode << std::endl;
				break;
			}

			// TODO:Kill the app if table says false

			// Terminate the process
			{
				std::lock_guard<std::mutex> lock(m_tableAccess);
				std::lock_guard<std::mutex> lock2(m_appNameAccess);

				if (!table[appName])
				{
					HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pi.dwProcessId);
					if (TerminateProcess(hProc, 0) == 0)
					{
						std::cerr << "Error terminating process: " << GetLastError() << std::endl;
					}
					else
					{
						std::cout << "The process PID: " << pi.dwProcessId << " was succesfully stopped." << std::endl;
						CloseHandle(hProc);
						appCeased = true;
						break;
					}

					CloseHandle(hProc);
				}
			}
		}

		// Close process and thread handles
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		return;
	}
#else

	if (proceed)
	{

		pid_t childPid = fork(); // Create a child process

		if (childPid == -1)
		{
			std::cerr << "Error creating a child process." << std::endl;
			return;
		}
		else if (childPid == 0) // Inside the child
		{
			// Child process code
			std::lock_guard<std::mutex> lock(m_appNameAccess);
			// Launch the application using exec
			if (execlp(appName.c_str(), appName.c_str(), NULL) == -1)
			{
				std::cerr << "Error launching the application." << std::endl;
				return;
			}
		}
		else // Inside the parent
		{
			// Parent process code

			while (true)
			{
				// Check if the child process has finished
				int status;
				pid_t result = waitpid(childPid, &status, WNOHANG);

				if (result == -1)
				{
					std::cerr << "Error waiting for the child process." << std::endl;
					return;
				}
				else if (result > 0)
				{
					// The child process has finished
					if (WIFEXITED(status))
					{
						std::cout << "Application exited with status: " << WEXITSTATUS(status) << std::endl;
						appCeased = true;
					}
					else
					{
						std::cout << "Application terminated abnormally." << std::endl;
					}
					break; // Exit the loop
				}
				// Terminate the process
				{
					std::lock_guard<std::mutex> lock(m_tableAccess);
					std::lock_guard<std::mutex> lock2(m_appNameAccess);

					if (!table[appName])
					{
						pid_t temp = childPid;
						if (kill(childPid, SIGTERM) != 0)
						{
							std::cerr << "Error terminating process: " << GetLastError() << std::endl;
						}
						else
						{
							std::cout << "The process PID: " << temp << " was succesfully terminated." << std::endl;
							appCeased = true;
							break;
						}
					}
				}
				// Sleep(1000);
				sleep(1);
			}
		}
	}
	else
	{
		return;
	}

#endif
	return;
}

int main()
{
	if (Network::Initialize())
	{
		std::cout << "Winsock API succesfully itialized." << std::endl;
		PMYDATA myData;
		Socket socket;
		if (socket.Create() == PResult::P_Success)
		{
			// #1
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(IPEndpoint("127.0.0.1", 4799)) == PResult::P_Success)
			{
				std::cout << "Succesfully conected to a server!" << std::endl;
				// The ACTUAL job is done here
				//  #2
				// start a thread #1 to listen for application's name
				myData = new MYDATA(&socket);
				std::thread userInput(HandleReceivingPackets, static_cast<void *>(myData));
				userInput.detach();

				while (appName == "")
				{
					// Sleep(1000);
					sleep(1);
				}
				// #3
				std::thread appThread(HandleApp);
				appThread.detach();

				while (true)
				{
					// when error occurs - break;

					// main thread processes sending info on app status
					if (!appCeased)
					{
						// #4
						Packet stringPacket(PacketType::PT_ChatMessage);
						stringPacket << std::string("App is running");

						HandleSendingPackets(socket, stringPacket);
						// Sleep(1000);
						sleep(1);
					}
					else
					{
						Packet stringPacket(PacketType::PT_ChatMessage);
						stringPacket << std::string("The app has ceased to exist");

						HandleSendingPackets(socket, stringPacket);
						appCeased = false;
						break;
					}
				}

				delete (myData);
			}
			else
			{
				std::cerr << "Failed to connect to a server." << std::endl;
			}
			socket.Close();
		}
		else
		{
			std::cout << "Socket failed to create." << std::endl;
		}
	}
	Network::Shutdown();
	#ifdef _WIN32
	system("pause");
	#endif;
}