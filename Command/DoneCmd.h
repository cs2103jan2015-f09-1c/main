//@author A0113736J
#pragma once
#include "commandinterface.h"
class DoneCmd : public CommandInterface {
public:
    DoneCmd(void);
	~DoneCmd(void);
	void prepareTaskId(int _TaskId);
	void recordInHistory(Task task);
	void verifyIndex();
	std:: string markDone();
    UIObject execute();
	UIObject undo();
	std::string getHelp()const;
	static const std::string NO_MATCHING_TASK;
	static const std::string DONE_MESSAGE;
	static const std::string UNDO_DONE_MESSAGE;


private:
	int taskId;
};