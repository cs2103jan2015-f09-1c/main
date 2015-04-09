//@Seow Yan Yi A0086626W
#pragma once
#include <exception>
#include <string>

class TaskNotFoundException : public std::exception {
private:
    std::string _message;

public:
    TaskNotFoundException(std::string msg);    
    ~TaskNotFoundException(void);
    virtual const char* what() const throw();
};

