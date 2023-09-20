#include "Network.h"


bool PNet::Network::Initialize()
{
    #ifdef _WIN32
    WSADATA wsadata;
    int result = WSAStartup(MAKEWORD(2, 2), &wsadata);

    if (result != 0)
    {
        std::cerr << "Failed to start up the winsock API." << std::endl;
        return false;
    }

    if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wVersion) != 2)
    {
        std::cerr << "Could not find the usable version of winsock API." << std::endl;
        return false;
    }
    #endif
    return true;
}

void PNet::Network::Shutdown()
{
    #ifdef _WIN32
    WSACleanup();
    #endif 
}
