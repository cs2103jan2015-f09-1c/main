#pragma once
#include "commandinterface.h"
class AddCmd : public CommandInterface {
public:
    AddCmd(void);
    ~AddCmd(void);
    void prepareTask(Task task);
    UIObject execute();
    UIObject undo();

private:
    Task _task;
};

