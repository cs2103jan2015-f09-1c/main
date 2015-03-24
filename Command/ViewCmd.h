#pragma once
#include "commandinterface.h"
class ViewCmd : public CommandInterface {
public:
    ViewCmd(void);
	~ViewCmd(void);
	void prepareDetail (std::string detail);
	void getSelectedTasks();
    UIObject execute();

private:
	std::string _detail;
	TaskList::TList selectedTasks;
};