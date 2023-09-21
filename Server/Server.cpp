//Server code
#include <PNet/IncludeMe.h>
#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <atomic>
#include <mutex>

std::atomic<bool> stopClientThread(false);
std::mutex consoleMutex; // Mutex for console access

using namespace PNet;

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

void HandleClientPackets(Socket& socket)
{	
	if (socket.Listen(IPEndpoint("127.0.0.1", 4790)) == PResult::P_Success)
	{
		std::cout << "Socket succesfully listening to port 4790." << std::endl;
		Socket newConnection;
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
				Packet stringPacket(PacketType::PT_ChatMessage);

				stringPacket << std::string("Hello from server to client!");
				// I try to send on the same connection.
				// 
				// You'll have to launch another thread here, to get user input and
				// send it on a newConnection socket.
				PResult result1 = newConnection.Send(stringPacket);

				if (result != PResult::P_Success)
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

void HandleUserInput(Socket socket)
{
		while (true) {
			// Get user input for the response
			std::string userInput;
			std::cout << "Enter <applicationNname.exe to start an app on client \nEnter the name again to stop it";
			std::getline(std::cin, userInput);

			if (userInput == "stop") {
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

			std::cout << "Attempting to send "<< userInput << "..."  << std::endl;
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

		
		Socket socket;
		PResult result = socket.Create();
		if(result == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;

			//std::thread clientThread(HandleClientPackets, socket);
			HandleClientPackets(socket);
			//std::thread userInput(HandleUserInput, socket);

			//clientThread.detach();
			//userInput.join();
		}
		else
		{
			std::cout << "Socket failed to create." << std::endl;
		}
	}
	Network::Shutdown();
	system("pause");
	return 0;
} 