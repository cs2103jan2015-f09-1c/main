#pragma once
#include "UIObject.h"
#include "TextUI.h"
class CommandInterface {
public:
    CommandInterface(void);
    virtual ~CommandInterface(void);
    UIObject execute();
};

