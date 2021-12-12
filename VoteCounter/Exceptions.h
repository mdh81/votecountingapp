#ifndef VCAPP_EXCEPTIONS_H
#define VCAPP_EXCEPTIONS_H
#include <string>
#include <stdexcept>

class InvalidCandidateException : public std::runtime_error {
    public:
        InvalidCandidateException(const std::string& msg) : std::runtime_error(msg) {
        }
        ~InvalidCandidateException() = default;
};

#endif