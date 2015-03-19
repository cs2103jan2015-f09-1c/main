#include "Controller.h"
#include "UIObject.h"
#include "TextUI.h"
#include "Storage.h"
#include "Logger.h"

int main(int argc, char *argv[]) {
    Logger::log("============= start program =============");
	Controller controllerService;

	TextUI::printWelcomeMsg();

    Storage *storage = Storage::getInstance();
    TaskList tasklist = storage->getTaskList();
    TaskList::TList today = tasklist.getToday();

    UIObject tasksToday;
    tasksToday.setHeaderText("Your tasks today:\n");
    tasksToday.setTaskList(today);
    TextUI::showOutput(tasksToday);
	
	while (true) {        
		std::string userInput;
		userInput = TextUI::getInput();

		UIObject controllerOutput;
		controllerOutput = controllerService.handleInput(userInput);
		TextUI::showOutput(controllerOutput);
	}

	return 0;
}
