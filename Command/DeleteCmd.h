#pragma once
#include "commandinterface.h"
class DeleteCmd : public CommandInterface {
public:
    DeleteCmd(void);
    ~DeleteCmd(void);
    void prepareTask(Task task);
	bool Delete (Task _task);
	void recordInHistory(Task task);
    UIObject execute();
    UIObject undo();

private:
    Task _task;
};