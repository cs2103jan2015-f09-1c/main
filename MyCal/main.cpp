#include "Controller.h"
#include "UIObject.h"
#include "TextUI.h"

void initMyCal() {
	//Perform initial setup
	TextUI::printWelcomeMsg();
}

int main(int argc, char *argv[]) {
	
	Controller controllerService;

	initMyCal();
	
	while (controllerService.isRunning()) {
		std::string userInput;
		userInput = TextUI::getInput();

		UIObject controllerOutput;
		controllerOutput = controllerService.handleInput(userInput);

		TextUI::showOutput(controllerOutput);
	}


	return 0;
}