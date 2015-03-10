#pragma once
#include <string>
#include "Task.h"

class Interpreter
{
public:
    static Task parseAddCmd(std::string input);
    static Task parseEditCmd(std::string input);

    Interpreter(void);
    ~Interpreter(void);
};

