#pragma once
#include "commandinterface.h"
#include "TaskList.h"


class SearchCmd : public CommandInterface {
public:
    SearchCmd(void);
    ~SearchCmd(void);
	void prepareList(TaskList::TList _List);
    UIObject execute();

private:
	TaskList::TList List;
};
