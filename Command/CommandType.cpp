#include "CommandType.h"

CommandType::CommandType(void) {
}

CommandType::~CommandType(void) {
}

CommandType::Command CommandType::determineCmdType(std::string userCmd) {
    std::string cmdString = getFirstWord(userCmd);

	if (cmdString == "add") {
		return CommandType::ADD;
	} else
	if (cmdString == "delete") {
		return CommandType::DELETE;
	} else
	if (cmdString == "edit") {
		return CommandType::EDIT;
	} else
	if (cmdString == "postpone") {
		return CommandType::POSTPONE;
	} else
	if (cmdString == "undo") {
		return CommandType::UNDO;
	} else
	if (cmdString == "search") {
		return CommandType::SEARCH;
	} else
	if (cmdString == "view") {
		return CommandType::VIEW;
	} else 
	if (cmdString == "block") {
		return CommandType::BLOCK;
	} else 
    if (cmdString == "confirm") {
		return CommandType::CONFIRM;
	} else 
    if (cmdString == "storage") {
		return CommandType::STORAGE;
	} else 
	if (cmdString == "exit") {
		return CommandType::EXIT_PROGRAM;
	} else {
		return CommandType::INVALID;
	}
}

std::string CommandType::getFirstWord(std::string userCmd) {
	std::istringstream iss(userCmd);
	std::string firstWord;
	iss >> firstWord;
	return firstWord;
}
