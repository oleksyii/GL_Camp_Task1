//Server code
#include <PNet/IncludeMe.h>
#include <iostream>

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
		if (socket.Create() == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Listen(IPEndpoint("127.0.0.1", 4790)) == PResult::P_Success)
			{
				std::cout << "Socket succesfully listening to port 4790." << std::endl;
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
		else
		{
			std::cout << "Socket failed to create." << std::endl;
		}
	}
	Network::Shutdown();
	system("pause");
	return 0;
} 