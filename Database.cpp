#include "Database.hpp"
#include <iostream>

void Database::storeMessage(const std::string& timestamp, const std::string& message) {
    messages[timestamp] = message;
    std::cout << "Stored message at " << timestamp << ": " << message << "\n";
}

std::string Database::getMessage(const std::string& timestamp) const {
    auto it = messages.find(timestamp);
    if (it != messages.end()) {
        return it->second;
    }
    return "Message not found.";
}
