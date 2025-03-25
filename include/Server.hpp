#ifndef SERVER_HPP
#define SERVER_HPP

#define _WIN32_WINNT 0x0600 // Windows Vista or later

#include <algorithm>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>
#include "Message.hpp"

class Server {
private:
    int serverSocket;
    int port;
    std::vector<int> clientSockets;
    std::mutex mtx;

    void handleClient(int clientSocket);

public:
    Server(int p);
    ~Server();

    void start();
    void broadcastMessage(const Message& message, int senderSocket);
};

#endif // SERVER_HPP
