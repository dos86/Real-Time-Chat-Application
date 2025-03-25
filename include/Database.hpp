#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <map>

class Database {
private:
    std::map<std::string, std::string> messages; // Timestamp -> Message

public:
    void storeMessage(const std::string& timestamp, const std::string& message);
    std::string getMessage(const std::string& timestamp) const;
};

#endif // DATABASE_HPP
