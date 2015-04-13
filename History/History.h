//@Seow Yan Yi A0086626W
#pragma once
#include "CommandType.h"
#include "State.h"

// In charge of storing the previous State and the Command associated with
// the most recent state change. This class facilitates the undoing of commands. 
// It is meant to be used inside the appropriate Command class if the Command 
// is "undoable". Undoable commands are those which modify the overall tasks
// a user has, for example add, edit, delete, change of storage location.
// Commands like view and search are not undoable because they do not change 
// the user's task list.
//
// Sample usage in AddCmd.cpp:
// CommandType::Command cmdType = CommandType::ADD;
// Task taskToAdd;
// // *initalize taskToAdd here*
// // *update storage with the new task here*
// State state;
// prevState->recordTask(taskToAdd);
// History* hist = History::getInstance();
// hist->saveCommand(CommandType::ADD);
// hist->saveState(state);
// 
// Note that in the above example, the task added is saved as part of the History. 
// The undo command can then getlastState() from History and perform a "undo"
// by deleting the task with the taskID of the newly added task.
// 
// getLastCommand() is used by the Controller so it knows which Command object's undo() function
// it should call - be it addCmdObj.undo() or editCmdObj.undo() etc...

class History {
public:
    static History* getInstance();
    static void resetInstance(); 

    CommandType::Command getPreviousCommand() const;
    void saveCommand(CommandType::Command cmd);
    State getPreviousState() const;
    void saveState(State state);
    void clearHistory();

private:
    History(void);
    ~History(void);
    static History* _instance;
    CommandType::Command _previousCommand;
    State _previousState;


};

