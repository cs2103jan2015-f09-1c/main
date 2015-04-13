//@author A0113955A
#include "SearchCmd.h"
#include "Storage.h"
#include "TaskList.h"


const std::string SearchCmd::NO_MATCHING_TASK = "There are no matching results";
const std::string SearchCmd::FOUND_TASK_MESSAGE = "Tasks found:";

SearchCmd::SearchCmd(void) {
}

SearchCmd::~SearchCmd(void) {
}

void SearchCmd::prepareList (TaskList::TList _List){
	List = _List;
}

UIObject SearchCmd::execute() {
    UIObject temp;
	Task task = List.front();
	//Search
	if (task.getTaskID() == 0){
		temp.setHeaderText (NO_MATCHING_TASK);
	}
	else if (task.getTaskID() == -1){
		temp.setHeaderText(getHelp());
	}
	else {
		temp.setHeaderText (FOUND_TASK_MESSAGE);
		temp.setTaskList (List);
	}

    //return UI Object 
    return temp;
}

std::string SearchCmd::getHelp() const{
	std::string help;

	std::string title = "***************** COMMAND HELP: SEARCH  *****************\n\n";

	std::string intro = "The search command allows you to look for a task \n\n"; 

	std::string pt1 = "1. This command can be invoked by typing search [Key word] \n";
	pt1 = pt1 + "Aliases: s, se \n\n";
	pt1 = pt1 + "Example: search meeting \n";
	pt1 = pt1 + "         s movies with John \n";
	pt1 = pt1 + "         se John\n";

	help = title + intro + pt1;

	return help;
}