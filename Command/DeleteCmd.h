#pragma once
#include "commandinterface.h"
class DeleteCmd : public CommandInterface {
public:
    DeleteCmd(void);
    ~DeleteCmd(void);
    void prepareTaskId(int _TaskId);
	void recordInHistory(Task task);
    UIObject execute();
    UIObject undo();

private:
    int TaskId;
};