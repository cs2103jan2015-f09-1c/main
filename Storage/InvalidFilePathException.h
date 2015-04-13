//@Seow Yan Yi A0086626W
#pragma once
#include <exception>
#include <string>

class InvalidFilePathException : public std::exception {
private:
    std::string _message;

public:
    InvalidFilePathException(std::string msg);    
    ~InvalidFilePathException(void);
    virtual const char* what() const throw();
};

