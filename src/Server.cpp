#include "Server.hpp"
#include <cstring>
#include <iostream>

Server::Server(int p) : port(p), serverSocket(-1) {}

Server::~Server() {
    if (serverSocket != -1) {
        close(serverSocket);
    }
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }
}

void Server::start() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create server socket.\n";
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind server socket.\n";
        return;
    }

    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Failed to listen on server socket.\n";
        return;
    }

    std::cout << "Server started. Listening on port " << port << ".\n";

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t addrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
        if (clientSocket < 0) {
            std::cerr << "Failed to accept client connection.\n";
            continue;
        }

        std::lock_guard<std::mutex> lock(mtx);
        clientSockets.push_back(clientSocket);
        std::cout << "New client connected.\n";

        std::thread clientThread(&Server::handleClient, this, clientSocket);
        clientThread.detach();
    }
}

void Server::handleClient(int clientSocket) {
    char buffer[1024] = {0};
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::lock_guard<std::mutex> lock(mtx);
            auto it = std::find(clientSockets.begin(), clientSockets.end(), clientSocket);
            if (it != clientSockets.end()) {
                clientSockets.erase(it);
            }
            close(clientSocket);
            std::cout << "Client disconnected.\n";
            break;
        }

        std::string message(buffer);
        memset(buffer, 0, sizeof(buffer));

        std::cout << "Received: " << message << "\n";
        broadcastMessage(Message("Client", message), clientSocket);
    }
}

void Server::broadcastMessage(const Message& message, int senderSocket) {
    std::lock_guard<std::mutex> lock(mtx);
    for (int clientSocket : clientSockets) {
        if (clientSocket != senderSocket) {
            send(clientSocket, message.content.c_str(), message.content.size(), 0);
        }
    }
}
