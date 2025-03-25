#ifndef CLIENT_HPP
#define CLIENT_HPP

#define _WIN32_WINNT 0x0600 // Windows Vista or later

#include <string>
#include <thread>
#include <mutex>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>

class Client {
private:
    int sock;
    std::string serverAddress;
    int port;
    bool isConnected;

public:
    Client(const std::string& address, int p);
    ~Client();

    void connectToServer();
    void sendMessage(const std::string& message);
    void receiveMessages();
    void run();
};

#endif // CLIENT_HPP
