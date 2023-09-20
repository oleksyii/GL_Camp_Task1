//Client code

#include <PNet/IncludeMe.h>
#include <iostream>
#include <unistd.h>

#define Sleep(duration) usleep(duration*1000)

using namespace PNet;

int main()
{
	if (Network::Initialize()) {
		std::cout << "Winsock API succesfully itialized." << std::endl;
		Socket socket;
		if (socket.Create() == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(IPEndpoint("127.0.0.1", 4790)) == PResult::P_Success)
			{
				std::cout << "Succesfully conected to a server!" << std::endl;

				Packet stringPacket(PacketType::PT_ChatMessage);
				stringPacket << std::string("This is my string packet");

				Packet integersPacket(PacketType::PT_IntegerArray);
				uint32_t arraySize = 6;
				uint32_t integerArray[6] = { 2, 5, 7, 1, 2, 9 };
				integersPacket << arraySize;
				for (auto integer : integerArray)
				{
					integersPacket << integer; 
				}

				while (true)
				{
					PResult result;
					
					if (rand() % 2 == 0)
					{
						result = socket.Send(stringPacket);
					}
					else
					{
						result = socket.Send(integersPacket);
					}

					if (result != PResult::P_Success)
						break; 

					std::cout << "Attempting to send chunk of data..." << std::endl;
					Sleep(500);
				}
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