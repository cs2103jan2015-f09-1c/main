//@Seow Yan Yi A0086626W
#pragma once
#include <exception>
#include <string>

class InvalidInputException : public std::exception {
private:
    std::string _message;

public:
    InvalidInputException(std::string msg);    
    ~InvalidInputException(void);
    virtual const char* what() const throw();
};

