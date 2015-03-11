#pragma once
#include <string>
#include "Task.h"

class Interpreter
{
private:
    static const size_t NUM_CHARS_STORAGE;

public:    
    static Task parseAddCmd(std::string input);
    static Task parseEditCmd(std::string input);
    static std::string parseStoreCmd(std::string input);

    Interpreter(void);
    ~Interpreter(void);
};

