//Server code
#include <PNet/IncludeMe.h>
#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <atomic>
#include <mutex>

#ifndef _WIN32
#include <unistd.h>
#define Sleep(duration) usleep(duration * 1000)
#endif // !_WIN32

// #define Sleep(duration) usleep(duration * 1000)

using namespace PNet;

std::atomic<bool> stopClientThread(false);
std::mutex consoleMutex; // Mutex for console access
Socket Specific_For_Connection;


typedef struct MyData {
	Socket socket;
	MyData(Socket ptr) : socket(ptr) {};
} MYDATA, *PMYDATA;



bool ProcessPacket(Packet& packet)
{
	switch (packet.GetPacketType())
	{
	case PacketType::PT_ChatMessage:
	{
		std::string chatMessage;
		packet >> chatMessage;
		std::cout << "Chat Message: " << chatMessage << std::endl;
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

void HandleClientConnection(void* in)
{	
	PMYDATA nn = static_cast<PMYDATA>(in);
	Socket socket = nn->socket;

	if (socket.Listen(IPEndpoint("127.0.0.1", 4799)) == PResult::P_Success)
	{
		std::cout << "Socket succesfully listening to port 4799." << std::endl;
		Socket& newConnection = Specific_For_Connection;
		// #1
		if (socket.Accept(newConnection) == PResult::P_Success)
		{
			std::cout << "New connection accepted." << std::endl;
			// #2
			// Launch thread to get a user input
			// The thread only gets user input from console and
			// sends it to newConnection immediately


			Packet packet;
			while (true)
			{
				PResult result = newConnection.Recv(packet);
				if (result != P_Success)
					break;
				if (!ProcessPacket(packet))
					break;
			}
			newConnection.Close();
		}
		else
		{
			std::cerr << "Failed to accept new connection" << std::endl;
		}
	}
	else
	{
		std::cerr << "Failed to listen a socket to port 4790" << std::endl;
	}
	socket.Close();
}

void HandleUserInput(void* in)
{
	PMYDATA nn = static_cast<PMYDATA>(in);
	Socket socket = nn->socket;
		while (true)
		{
			// Get user input for the response
			std::string userInput;

			{
				std::lock_guard<std::mutex> lock(consoleMutex);
				std::cout << "Enter <applicationNname.exe to start an app on client \nEnter the name again to stop it:" << std::endl;
			}
			
			std::getline(std::cin, userInput);

			if (userInput == "stop")
			{
				stopClientThread = true;

				{
					std::lock_guard<std::mutex> lock(consoleMutex);
					std::cout << "Sending stop message to the client." << std::endl;
				}

				break;
			}

			Packet stringPacket(PacketType::PT_ChatMessage);
			stringPacket << userInput;
			

			PResult result;
			result = socket.Send(stringPacket);

			if (result != PResult::P_Success)
				break;

			std::cout << "Attempting to send "<< userInput << " ..."  << std::endl;
			//std::cout << "Attempting to send Hehlo ..." << std::endl;
			Sleep(1000);
		}
}

int main()
{
		
	if (Network::Initialize()) {
		std::cout << "Winsock API succesfully itialized." << std::endl;

		//IPEndpoint test("www.google.com", 8080);
		//if (test.GetIPVersion() == IPVersion::IPv4)
		//{
		//	std::cout 
		//		<< "Hostname: " << test.GetHostName() << "\n"
		//		<< "IP: " << test.GetIpString() << "\n"
		//		<< "Port: " << test.GetPort() << "\n"
		//		<< "IP Bytes..." << std::endl;
		//	for (auto& digit : test.GetIPBytes())
		//	{
		//		std::cout << (int)digit << std::endl;
		//	}
		//}
		//else
		//{
		//	std::cerr << "This is not a valid ipv4 addresss." << std::endl;
		//}
		PMYDATA myData;
		Socket socket;
		PResult result = socket.Create();
		if(result == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			
			//Create a new thread to handle receiving from a Client
			myData = new MYDATA(socket);
			std::thread clientHandle(HandleClientConnection, static_cast<void*>(myData));
			clientHandle.detach();
			

			while (!Specific_For_Connection)
			{
				std::cout << "Awaiting for connection ..." << std::endl;
				// Sleep(1000);
				sleep(1);
			}

			myData = new MYDATA(Specific_For_Connection);
			std::thread userInput(HandleUserInput, static_cast<void*>(myData));
			userInput.join();
			delete(myData);
		}
		else
		{
			std::cout << "Socket failed to create." << std::endl;
		}

	}
	Network::Shutdown();
	#ifdef _WIN32
	system("pause");
	#endif
	return 0;
} 