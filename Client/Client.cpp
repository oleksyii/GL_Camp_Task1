//Client code

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

#include <PNet/IncludeMe.h>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#define Sleep(duration) usleep(duration*1000)
#endif // !_WIN32

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

void HandleServerPakets(Socket& socket)
{
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
	//while (true)
	//{
		PResult result;
		result = socket.Send(packet);

		//if (result != PResult::P_Success)
		//	break;

		std::cout << "Attempting to send chunk of data..." << std::endl;
	//	Sleep(1000);
	//}
}


int main()
{
	if (Network::Initialize()) {
		std::cout << "Winsock API succesfully itialized." << std::endl;
		Socket socket;
		if (socket.Create() == PResult::P_Success)
		{
			// #1
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(IPEndpoint("127.0.0.1", 4790)) == PResult::P_Success)
			{
				std::cout << "Succesfully conected to a server!" << std::endl;
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
				// Make the app running
				Packet stringPacket(PacketType::PT_ChatMessage);
				stringPacket << std::string("App is running");

				//sending to server
				HandleSendingPackets(socket, stringPacket);
				std::cout << "Sending packets succesfully." << std::endl;
				//receiving from a Server
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


				std::cout << "Trying to Recv from the same socket." << std::endl;
				Packet packet;
				socket.Recv(packet);
				ProcessPacket(packet);

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