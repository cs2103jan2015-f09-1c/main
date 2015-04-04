#pragma once
#include <string>
#include "UIObject.h"
#include "CommandType.h"

class Controller {
private:
    static UIObject undoCommand(CommandType::Command cmdType);
	static const size_t NUM_CHARS_DONE;
	static const size_t NUM_CHARS_DELETE;

public:
    static UIObject handleInput(std::string input);
    
    Controller(void);
    ~Controller(void);
};

