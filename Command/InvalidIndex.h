#pragma once
#include <exception>
#include <string>

class InvalidIndex : public std::exception {
private:
    std::string _message;

public:
    InvalidIndex(std::string msg);    
    ~InvalidIndex(void);
    virtual const char* what() const throw();
};

