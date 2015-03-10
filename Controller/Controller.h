#pragma once
#include <string>
#include "UIObject.h"

class Controller {
private:
    bool _isRunning;

public:

    bool isRunning() const;
    UIObject handleInput(std::string input);
    
    Controller(void);
    ~Controller(void);
};

