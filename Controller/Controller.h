#pragma once
#include <string>
#include "UIObject.h"

class Controller {
public:
    UIObject handleInput(std::string input);
    
    Controller(void);
    ~Controller(void);
};

