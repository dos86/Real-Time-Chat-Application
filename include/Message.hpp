#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

struct Message {
    std::string sender;
    std::string content;

    // Default constructor
    Message() : sender(""), content("") {}

    // Parameterized constructor
    Message(const std::string& s, const std::string& c) : sender(s), content(c) {}
};

#endif // MESSAGE_HPP
