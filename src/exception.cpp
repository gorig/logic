#include <exception.h>

Exception::Exception(const std::string &message)
    : _message(message) {}

const char *Exception::what() const noexcept {
    return _message.c_str();
}
