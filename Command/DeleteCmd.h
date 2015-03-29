#pragma once
#include "commandinterface.h"
class DeleteCmd : public CommandInterface {
public:
    DeleteCmd(void);
    ~DeleteCmd(void);
    void prepareTask(Task task);
	unsigned GetTaskId ();
	int ConvertStrtoNum (std::string str);
	bool CheckTask (Task _task);
	void recordInHistory(Task task);
    UIObject execute();
    UIObject undo();

private:
    Task _task;
};