#pragma once
#include "commandinterface.h"
class DeleteCmd : public CommandInterface {
public:
    DeleteCmd(void);
    ~DeleteCmd(void);
    void prepareTask(Task task);
    UIObject execute();

private:
    Task _task;
};
