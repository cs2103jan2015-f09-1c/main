#pragma once
#include "commandinterface.h"
class DeleteCmd : public CommandInterface {
public:
    DeleteCmd(void);
    ~DeleteCmd(void);
    void prepareTaskId(int _TaskId);
    UIObject execute();
    UIObject undo();
	std::string getHelp()const;

	static const std::string NO_MATCHING_TASK;
	static const std::string NO_TASK_MESSAGE;
	static const std::string REMAINING_TASK_MESSAGE;
	static const std::string UNDO_MESSAGE;
private:
    void recordInHistory(Task task);
    int TaskId;
};