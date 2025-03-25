#include "Client.hpp"
#include <cstring>
#include <iostream>

Client::Client(const std::string& address, int p)
    : serverAddress(address), port(p), isConnected(false) {}

Client::~Client() {
    if (isConnected) {
        close(sock);
    }
}

void Client::connectToServer() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket.\n";
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, serverAddress.c_str(), &serverAddr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to server.\n";
        return;
    }

    isConnected = true;
    std::cout << "Connected to server.\n";
}

void Client::sendMessage(const std::string& message) {
    if (!isConnected) {
        std::cerr << "Not connected to server.\n";
        return;
    }

    send(sock, message.c_str(), message.size(), 0);
}

void Client::receiveMessages() {
    char buffer[1024] = {0};
    while (isConnected) {
        int bytesReceived = recv(sock, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            std::cerr << "Disconnected from server.\n";
            isConnected = false;
            break;
        }
        std::cout << "Server: " << buffer << "\n";
        memset(buffer, 0, sizeof(buffer));
    }
}

void Client::run() {
    connectToServer();
    std::thread receiverThread(&Client::receiveMessages, this);
    receiverThread.detach();

    std::string input;
    while (isConnected) {
        std::getline(std::cin, input);
        sendMessage(input);
    }
}
