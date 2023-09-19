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

				char buffer[256];
				strcpy_s(buffer, "Hello world from client!\0");
				int bytesSent = 0;
				int result = PResult::P_Success;
				while (result == PResult::P_Success)
				{
					result = socket.Send(buffer, sizeof(buffer), bytesSent);
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