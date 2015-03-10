#pragma once
#include "UIObject.h"

class CommandInterface {
public:
    CommandInterface(void);
    virtual ~CommandInterface(void);
    UIObject execute();
};

