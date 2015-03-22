#include "AddCmd.h"
#include "Storage.h"
#include "TaskList.h"

AddCmd::AddCmd(void) {
}


AddCmd::~AddCmd(void) {
}

void AddCmd::prepareTask(Task task) {
    _task = task;
}

UIObject AddCmd::execute() {
    //get current tasks
    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

    //set the taskid
    _task.setTaskID(storage->getNextID());

    //add the task
    taskList.add(_task);

    //update storage
    storage->updateStorage(taskList);    

    //returns the day's tasks
    TaskList::TList tasksThatDay;
    tasksThatDay = taskList.getDay(_task.getTaskBegin());

    UIObject addObj;
    addObj.setHeaderText("Task added.");
    addObj.setTaskList(tasksThatDay);

    return addObj;
}

UIObject AddCmd::undo() {
    UIObject undoMessage;
    //undo stuff
    return undoMessage;
}