//@author A0086626W
#pragma once
#include "commandinterface.h"
class AddCmd : public CommandInterface {
public:
    AddCmd(void);
    ~AddCmd(void);
    void prepareTask(Task task);
	void recordInHistory (Task task);
    UIObject execute();
    UIObject undo();

	std::string getHelp() const;
	static const std::string ADD_MESSAGE;
	static const std::string UNDO_MESSAGE;
private:
    Task _task;
};

