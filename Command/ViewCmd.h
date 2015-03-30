#pragma once
#include "commandinterface.h"
class ViewCmd : public CommandInterface {
public:
    ViewCmd(void);
	~ViewCmd(void);
	void prepareDetail (std::string detail);
	TaskList::TList getSelectedTasks();
    UIObject execute();
	static const std::string NO_TASK_MESSAGE;

private:
	std::string _detail;
	time_t getDayPosition(int index);
};