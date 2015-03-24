#include "EditCmd.h"
#include "Storage.h"
#include "TaskList.h"


EditCmd::EditCmd(void) {
}


EditCmd::~EditCmd(void) {
}

void EditCmd::prepareTask(Task task) {
    _task = task;
}

UIObject EditCmd::execute() {
    UIObject temp;

    Storage* storage = Storage::getInstance();
    TaskList taskList = storage->getTaskList();

	//edit the task
	taskList.update(_task);

	//return UI Object
	temp.setHeaderText("Successfuly Edited");

	/*		
    //edit the task
	TaskList::taskIt it;
	TaskList::TList _taskList = taskList.getAll();
    for (it = _taskList.begin(); it != _taskList.end(); ++it) {
        unsigned targetId = _task.getTaskID();
        unsigned curId = it->getTaskID();

        if (targetId == curId) { //found
			temp.setHeaderText("-----Editing task "+std::to_string(it->getTaskID())+"-----");
			
        }
		else{ //not found
			temp.setHeaderText("-----Task not found-----");			
		}
    }
	*/

    storage->updateStorage(taskList);    


    return temp;
}

UIObject EditCmd::undo() {
    UIObject undoMessage;
    //undo stuff
    return undoMessage;
}