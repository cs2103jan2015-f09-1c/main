#pragma once
#include "commandinterface.h"
class EditCmd : public CommandInterface {
public:
    EditCmd(void);
    ~EditCmd(void);
    void prepareTask(Task task);
    UIObject execute();
    UIObject undo();

private:
    static const std::string UNDO_MESSAGE;
    void recordInHistory(Task task);
    Task _task;
};
