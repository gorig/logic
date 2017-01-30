#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
public:
    Exception(const std::string &message);
    virtual const char* what() const noexcept override;

private:
    std::string _message;
};