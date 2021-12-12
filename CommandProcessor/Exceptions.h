#ifndef VCAPP_EXCEPTIONS_H
#define VCAPP_EXCEPTIONS_H
#include <string>

class InvalidCommandException : public std::runtime_error {
    public:
        InvalidCommandException(const std::string& msg) : std::runtime_error(msg) {
        }
        ~InvalidCommandException() = default;
        /*const char* what() const _NOEXCEPT override {
            return m_msg.data();
        }*/
    private:
        std::string m_msg;
};


#endif