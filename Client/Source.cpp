//Client code

#include <PNet/IncludeMe.h>
#include <iostream>

using namespace PNet;

int main()
{
	if (Network::Initialize()) {
		std::cout << "Winsock API succesfully itialized." << std::endl;
	}
	Network::Shutdown();

}