#include <iostream>
#include "include/Server.hpp"
#include "include/Client.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./RealTimeChat [server|client] [port]\n";
        return 1;
    }

    std::string mode = argv[1];
    int port = std::stoi(argv[2]);

    if (mode == "server") {
        Server server(port);
        server.start();
    } else if (mode == "client") {
        Client client("127.0.0.1", port);
        client.run();
    } else {
        std::cerr << "Invalid mode. Use 'server' or 'client'.\n";
    }

    return 0;
}
