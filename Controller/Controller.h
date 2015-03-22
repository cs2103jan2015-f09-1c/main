#pragma once
#include <string>
#include "UIObject.h"
#include "CommandType.h"

class Controller {
private:
    UIObject undoCommand(CommandType::Command cmdType);

public:
    UIObject handleInput(std::string input);
    
    Controller(void);
    ~Controller(void);
};

