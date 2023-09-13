#include <iostream>
#include <cstring>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>

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
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use localhost

    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error: Unable to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    const char* applicationName = "notepad.exe"; // Replace with the desired application name

    // Send the application name to the server
    if (send(clientSocket, applicationName, strlen(applicationName), 0) == SOCKET_ERROR) {
        std::cerr << "Error: Failed to send the application name to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    char response[1024];
    int bytesRead = recv(clientSocket, response, sizeof(response), 0);
    if (bytesRead == SOCKET_ERROR) {
        std::cerr << "Error: Failed to receive a response from the server." << std::endl;
    }
    else {
        response[bytesRead] = '\0';
        std::cout << "Server response: " << response << std::endl;
    }

    while (true) {
        char status[1024];
        bytesRead = recv(clientSocket, status, sizeof(status), 0);
        if (bytesRead == SOCKET_ERROR) {
            std::cerr << "Error: Failed to receive application status from the server." << std::endl;
            break;
        }
        else if (bytesRead == 0) {
            std::cerr << "Server closed the connection." << std::endl;
            break;
        }
        else {
            status[bytesRead] = '\0';
            std::cout << "Application status: " << status << std::endl;

            // Check if the application has stopped
            if (strcmp(status, "Application Stopped") == 0) {
                std::cout << "The application has stopped." << std::endl;
                break; // Exit the loop
            }
        }
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
