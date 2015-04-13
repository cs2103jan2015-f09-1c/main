//@author A0086626W
#pragma once
#include "UIObject.h"
#include "TextUI.h"

class CommandInterface {
public:
    CommandInterface(void);
    virtual ~CommandInterface(void);
    virtual UIObject execute() = 0; 

    // Undo the previous command
    //
    // General flow is as follows:
    // Before a Command object performs the relevant action, save the current
    // "state" in History. This could be a task object which is going to be updated, or
    // a storage location which is going to be changed, for example.
    // Only after saving the previous state do we proceed to perform the action
    // When undo() is called, retrieve the old state from History and reverse what is
    // changed to its previous state.
    //
    // Currently only the most recent undo-able command can be undone.
    // Below are some examples in pseudo code:
    //
    // action: ADD task x
    // - state to store: newly created task x
    // - undo implementation: retrieve taskID of newly created task and
    // call delete using the taskID 
    //
    // action: EDIT task x
    // - state to store: task before edit
    // - undo implementation: call edit again and pass in the previous task. 
    //
    // action: DELETE task x
    // - state to store: task before delete
    // - undo implementation: call add and pass in copy of task
    //
    // action: change STORAGE location from x to y
    // - state to store: previous storage location, x.
    // - undo implementation: call change storage again, this time changing from y to x.
    //
    // History should be cleared after undoing. If user types "undo" again, he will not
    // "undo" the undo - which is a confusing behavior to have.


    virtual UIObject undo(); 
};

