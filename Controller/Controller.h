#pragma once
#include <string>
#include "UIObject.h"
#include "CommandType.h"

class Controller {
private:
    static UIObject undoCommand(CommandType::Command cmdType);

public:
    static UIObject handleInput(std::string input);
    
    Controller(void);
    ~Controller(void);
};

