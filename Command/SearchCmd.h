//@Pham Thi Hong A0113955A
#pragma once
#include "commandinterface.h"
#include "TaskList.h"


class SearchCmd : public CommandInterface {
public:
    SearchCmd(void);
    ~SearchCmd(void);
	void prepareList(TaskList::TList _List);
    UIObject execute();
	std::string getHelp()const;

	static const std::string NO_MATCHING_TASK;
	static const std::string FOUND_TASK_MESSAGE;

private:
	TaskList::TList List;
};
