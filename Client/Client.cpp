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
//Client code
#include <PNet/IncludeMe.h>
#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <atomic>
#include <mutex>
#include <locale>
#include <codecvt>
#ifndef _WIN32
#include <unistd.h>
#define Sleep(duration) usleep(duration*1000)
#endif // !_WIN32

using namespace PNet;

std::atomic<bool> stopClientThread(false);
std::mutex consoleMutex; // Mutex for console access
std::string appName = "";
std::mutex appNameMutex;

typedef struct MyData {
	Socket* socket;
	MyData(Socket* ptr) : socket(ptr) {};
} MYDATA, * PMYDATA;


bool ProcessPacket(Packet& packet)
{
	switch (packet.GetPacketType())
	{
	case PacketType::PT_ChatMessage:
	{
		std::lock_guard<std::mutex> lock(appNameMutex);
		packet >> appName;

		// TODO:
		// Remake the thing to be a dictionary to know whether app 
		// should be stopped or not

		//std::string chatMessage;
		//packet >> chatMessage;
		//std::cout << "Chat Message: " << chatMessage << std::endl;
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
void HandleServerPakets(void* in)
{
	PMYDATA nn = static_cast<PMYDATA>(in);
	Socket socket = *(nn->socket);

	if (socket.Listen(IPEndpoint("127.0.0.1", 4790)) == PResult::P_Success)
	{
		std::cout << "Socket succesfully listening to port 4791." << std::endl;
		Socket newConnection;
		if (socket.Accept(newConnection) == PResult::P_Success)
		{
			std::cout << "New connection accepted." << std::endl;

			Packet packet;
			while (true)
			{
				PResult result = newConnection.Recv(packet);
				if (result != PResult::P_Success)
					break;

				if (!ProcessPacket(packet))
					break;

			}
			newConnection.Close();
		}
	}

}

void HandleSendingPackets(Socket& socket, Packet packet)
{
		PResult result;
		result = socket.Send(packet);

		if (result != PResult::P_Success)
			return;

		std::cout << "Attempting to send chunk of data..." << std::endl;

}

void HandleApp()
{
	// Define the path to the application you want to launch
		// Convert the UTF-8 string to a UTF-16 wstrin
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring utf16String = converter.from_bytes(appName);

	// CreateProcess parameters
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// Launch the application
	if (!CreateProcess(
		NULL,                 // Application name (use NULL to use command line)
		const_cast<wchar_t*>(utf16String.c_str()), // Command line
		NULL,                 // Process security attributes
		NULL,                 // Thread security attributes
		FALSE,                // Inherit handles
		0,                    // Creation flags
		NULL,                 // Use parent's environment
		NULL,                 // Use parent's current directory
		&si,                  // STARTUPINFO structure
		&pi                   // PROCESS_INFORMATION structure
	)) 
	{
		std::cerr << "Error creating process: " << GetLastError() << std::endl;
		return;
	}

	// Wait for the application to finish, checking every one second
	DWORD exitCode;
	while (true) 
	{
		if (WaitForSingleObject(pi.hProcess, 1000) == WAIT_OBJECT_0 &&
			GetExitCodeProcess(pi.hProcess, &exitCode)) 
		{
			stopClientThread = true;
			std::cout << "Application exited with code: " << exitCode << std::endl;
			break;
		}
	}

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

}


int main()
{
	if (Network::Initialize()) {
		std::cout << "Winsock API succesfully itialized." << std::endl;
		PMYDATA myData;
		Socket socket;
		if (socket.Create() == PResult::P_Success)
		{
			// #1
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(IPEndpoint("127.0.0.1", 4790)) == PResult::P_Success)
			{
				std::cout << "Succesfully conected to a server!" << std::endl;
				//The ACTUAL job is done here
				// #2
				//start a thread #1 to listen for application's name
				myData = new MYDATA(&socket);
				std::thread userInput(HandleServerPakets, static_cast<void*>(myData));
				userInput.detach();

				while (true)
				{
					if (appName == "")
						Sleep(1000);
					else
						break;

				}
				// #3
				//TODO:start a thread to handle the application

				std::thread appThread(HandleApp);
				appThread.detach();

				while (true)
				{
					//when error occurs - break;



					//main thread processes sending info on app status
					if(!stopClientThread)
					{
						// #4
						Packet stringPacket(PacketType::PT_ChatMessage);
						stringPacket << std::string("App is running");

						HandleSendingPackets(socket, stringPacket);
						Sleep(1000);
					}
					else
					{
						Packet stringPacket(PacketType::PT_ChatMessage);
						stringPacket << std::string("App has deceased it's existance");

						HandleSendingPackets(socket, stringPacket);
						stopClientThread = false;
						break;
					}
				}
				// Handle receiveng from Server 
				// while(true)
				// {
				//
				// socket.Recv() ...
				// if (name recieved is present is names vector, then change the value)
				// else
				// launch a thread to control an app
				// }
				// 

				// 
				// Create a thread for each app to launch. Thread creates an app, checks 
				// for its finish and checks for a variable from stop-words vector to change.
				// If the variable changes - kills an app. Main thread then sends notification
				// about application's disruptance
				// 
				// Or
				// 
				// You'll have to laucnh a thread here to listen of for a '"stop-word"
				// when the word arrives, change the atomic variable to inform main thread 
				// that the app shoud be stopped. Then send a packet about application's
				// disruptance

				delete(myData);
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
	system("pause"); 
}