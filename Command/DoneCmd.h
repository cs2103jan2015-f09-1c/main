#pragma once
#include "commandinterface.h"
class DoneCmd : public CommandInterface {
public:
    DoneCmd(void);
	~DoneCmd(void);
	void prepareIndex (int index);
	void recordInHistory(Task task);
	void verifyIndex();
	std:: string markDone();
    UIObject execute();
	UIObject undo();

private:
	int _index;
	TaskList::TList selectedTasks;
};