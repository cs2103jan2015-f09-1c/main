//@author A0113955A
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
	std::string getHelp()const;

	static const std::string NO_MATCHING_TASK;
	static const std::string NO_TASK_MESSAGE;
	static const std::string REMAINING_TASK_MESSAGE;
	static const std::string UNDO_MESSAGE;
private:
    int TaskId;
};