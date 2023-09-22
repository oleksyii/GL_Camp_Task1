#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <process.h> // For _beginthreadex

#pragma warning(disable : 4996)

// Function to handle client connections
unsigned int __stdcall HandleClient(void* data);

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error: Unable to initialize Winsock." << std::endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error: Unable to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888); // Port number
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error: Unable to bind socket." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cerr << "Error: Unable to listen for connections." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening..." << std::endl;

    while (true) {
        sockaddr_in clientAddr;
        int clientAddrLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error: Unable to accept client connection." << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        // Create a thread to handle the client connection
        unsigned int threadId;
        _beginthreadex(nullptr, 0, HandleClient, &clientSocket, 0, &threadId);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}

// Function to handle client connections
unsigned int __stdcall HandleClient(void* data) {
    SOCKET clientSocket = *reinterpret_cast<SOCKET*>(data);
    char buffer[1024];
    int bytesRead;

    // Receive application name from the client
    bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == SOCKET_ERROR) {
        std::cerr << "Error: Failed to receive application name from the client." << std::endl;
        closesocket(clientSocket);
        return 1;
    }
    buffer[bytesRead] = '\0';
    std::cout << "Received application name: " << buffer << std::endl;

    // Launch the requested application
    STARTUPINFO startupInfo;
    PROCESS_INFORMATION processInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);

    std::wstring wc(sizeof(buffer), L'#');
    mbstowcs(&wc[0], buffer, sizeof(buffer));

    if (CreateProcess(nullptr, &wc[0], nullptr, nullptr, false, 0, nullptr, nullptr, &startupInfo, &processInfo)) {
        std::cout << "Successfully launched the application." << std::endl;
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        send(clientSocket, "Success", 7, 0); // Send success message to the client
    
        // Wait for the application to exit and track its status
        while (true) {
            DWORD exitCode;
            if (GetExitCodeProcess(processInfo.hProcess, &exitCode) && exitCode != STILL_ACTIVE) {
                std::cout << "Application has exited." << std::endl;

                // Notify the client that the application has stopped
                send(clientSocket, "Application Stopped", 20, 0);
                break;
            }

            Sleep(1000); // Sleep for 1 second
            send(clientSocket, "Running", 8, 0); // Send application status message to the client
        }
    }
    else {
        std::cerr << "Error: Failed to launch the application." << std::endl;
        send(clientSocket, "Failure", 7, 0); // Send failure message to the client
    }

    while (true) {
        // Check if the application is still running
        DWORD exitCode;
        if (GetExitCodeProcess(processInfo.hProcess, &exitCode) && exitCode != STILL_ACTIVE) {
            std::cout << "Application has exited." << std::endl;
            send(clientSocket, "Application Exited", 19, 0); // Send application exit message to the client
            break;
        }

        Sleep(1000); // Sleep for 1 second
        send(clientSocket, "Running", 8, 0); // Send application status message to the client
    }

    closesocket(clientSocket);
    return 0;
}
