#include "Controller.h"
#include "UIObject.h"
#include "TextUI.h"
#include "Storage.h"
#include <iostream>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

void configureLogging() {
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "false");
    el::Loggers::reconfigureLogger("default", defaultConf);
    LOG(INFO) << "LOG SESSION BEGIN <<<<<<<<<<<";
}

int main(int argc, char *argv[]) {
    START_EASYLOGGINGPP(argc, argv);
    configureLogging();

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
