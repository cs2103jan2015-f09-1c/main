#include "TaskMaster.h"
#include "Storage.h"
/*
DS::UIObject TaskMaster::addTask(DS::TASK task) {
    DS::UIObject addSuccess;
    DS::TaskList allTasks = storageObj->getAllTasks();

    //Code to insert "task" into "allTasks" below.

    //How? Loop through every SINGLE_DAY until we find the day we want.
    //Then insert into tasksThisDay (which is just a vector of Tasks)
    //Remember to insert in correct order. That is, the tasks are
    //arranged according to their taskStart times
    //
    //Add taskID to the new Task too. 
    //How? get the maximum ID we currently have and add 1 to it.
    //There is a function in Storage class getMaxID. But Storage
    //class not built finish yet, so just put any fake value for the moment.
    //
    //Apart from that, store a copy of the Task before and after change.
    //Then save it into a CHANGES object
    //
    //finally, when all is done call Storage::updateStorage(change, updated_tasklist)
    //
    //Make a UIObject with header text 
    //"Sucessfully added "<task name here>" to <the date here>.
    //and TaskList filled with tasks of the particular date only
    //this will be returned and the TextUI will use it to feedback to user
    return addSuccess;
}

DS::UIObject TaskMaster::deleteTask(DS::TASK task) {
    DS::UIObject delSuccess;
	DS::TaskList allTasks = storageObj->getAllTasks();
    DS::dayIter iter;
	for (iter = taskList.begin(); iter != taskList.end(); ++iter) {
		DS::SINGLE_DAY curDay = *iter;
		if (task.taskID == *iter){
			taskList.erase(*iter);
			break;
		}
	}
    return delSuccess;
}

DS::UIObject TaskMaster::editTask(DS::TASK task) {
    DS::UIObject editSuccess;

    return editSuccess;
}

DS::UIObject TaskMaster::markTask(DS::TASK task) {
    DS::UIObject markSuccess;

    return markSuccess;
}

DS::UIObject TaskMaster::undoTask() {
    DS::UIObject undoSuccess;

    return undoSuccess;
}

TaskMaster::TaskMaster(void) {
}


TaskMaster::~TaskMaster(void) {
}

*/
