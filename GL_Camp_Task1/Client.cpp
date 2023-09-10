#include <iostream>
#include <cstring>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error: Unable to initialize Winsock." << std::endl;
        return 1; // Return an error code to indicate failure
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error: Unable to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888); // Port number
    //unsigned char buf[sizeof(struct in6_addr)];
    //serverAddr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", buf);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use localhost

    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error: Unable to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == SOCKET_ERROR) {
        std::cerr << "Error: Failed to receive data from the server." << std::endl;
    }
    else if (bytesRead == 0) {
        std::cerr << "Connection closed by the server." << std::endl;
    }
    else {
        buffer[bytesRead] = '\0'; // Null-terminate the received data
        std::cout << "Received: " << buffer << std::endl;
    }

    closesocket(clientSocket);
    WSACleanup();

    getchar();
    
    return 0;
}
