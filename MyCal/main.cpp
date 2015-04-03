#include "Controller.h"
#include "UIObject.h"
#include "TextUI.h"
#include "Storage.h"
#include "MCLogger.h"

void printTasksToday() {
    Storage *storage = Storage::getInstance();
    TaskList tasklist = storage->getTaskList();
    TaskList::TList today = tasklist.getToday();

    UIObject tasksToday;

    if (today.empty()) {
        tasksToday.setHeaderText("No tasks for today.");

    } else {
        tasksToday.setHeaderText("Your tasks today:");
        tasksToday.setTaskList(today);
    }

    TextUI::showOutput(tasksToday);
}

int main(int argc, char *argv[]) {
    MCLogger::log("============= start program =============");

	TextUI::printWelcomeMsg();
	printTasksToday();

	while (true) {        
		std::string userInput;
		userInput = TextUI::getInput();
		
		MCLogger::log("User input: " + userInput);
		UIObject controllerOutput = Controller::handleInput(userInput);

		TextUI::clearScreen();
		TextUI::showOutput(controllerOutput);
	}

	return 0;
}
