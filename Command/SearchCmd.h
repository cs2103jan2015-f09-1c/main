#pragma once
#include "commandinterface.h"


class SearchCmd : public CommandInterface {
public:
    SearchCmd(void);
    ~SearchCmd(void);
	void prepareTask(Task task);
    void prepareSearch(std::string keyword);
    UIObject execute();

private:
    std::string _keyword;
	Task _task;
	bool Search(std::string keyword, Task task){
		std::string line = task.getTaskName();
		if (line.find(keyword) != std::string::npos){
			return true;
	}
	else{
		return false;
	}
	}
};
