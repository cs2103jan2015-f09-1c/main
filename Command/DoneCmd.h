#pragma once
#include "commandinterface.h"
class DoneCmd : public CommandInterface {
public:
    DoneCmd(void);
	~DoneCmd(void);
	void prepareIndex (int index);
    UIObject execute();

private:
	int _index;
	TaskList::TList selectedTasks;
};