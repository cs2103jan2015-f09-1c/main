#pragma once
#include "commandinterface.h"
class EditCmd : public CommandInterface {
private:
    void recordInHistory(Task task);
    Task _task;

public:
    EditCmd(void);
    ~EditCmd(void);
    void prepareTask(Task task);
    UIObject execute();
    UIObject undo();
};
