#ifndef VCAPP_EXCEPTIONS_H
#define VCAPP_EXCEPTIONS_H
#include <string>
#include <stdexcept>

class InvalidCommandException : public std::runtime_error {
    public:
        InvalidCommandException(const std::string& msg) : std::runtime_error(msg) {
        }
        ~InvalidCommandException() = default;
};

#endif