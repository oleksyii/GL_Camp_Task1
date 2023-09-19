//Client code

#include <PNet/IncludeMe.h>
#include <iostream>

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

				std::string buffer = "";
				buffer.resize(PNet::g_MaxPacketSize + 1);
				memset(&buffer[0], 'A', PNet::g_MaxPacketSize + 1);
								
				while (true)
				{
					uint32_t bufferSize = buffer.size();
					bufferSize = htonl(bufferSize);
					PResult result = socket.SendAll(&bufferSize, sizeof(uint32_t));
					if (result != PResult::P_Success)
						break;

					result = socket.SendAll(buffer.data(), buffer.size());
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