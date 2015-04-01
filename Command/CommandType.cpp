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
		return CommandType::DEL;
	} else
	if (cmdString == "edit") {
		return CommandType::EDIT;
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
	if(cmdString == "done"){
		return CommandType::DONE;
	}else
    if (cmdString == "storage") {
		return CommandType::STORAGE;
	} else 
	if (cmdString == "exit") {
		return CommandType::EXIT_PROGRAM;
	} else {
		return CommandType::INVALID;
	}
}

std::string CommandType::cmdToString(Command cmdType) {
	if (cmdType == ADD) {
		return "CommandType::ADD";
	} else
	if (cmdType == DEL) {
		return "CommandType::DEL";
	} else
	if (cmdType == EDIT) {
		return "CommandType::EDIT";
	} else
	if (cmdType == UNDO) {
		return "CommandType::UNDO";
	} else
	if (cmdType == SEARCH) {
		return "CommandType::SEARCH";
	} else
	if (cmdType == VIEW) {
		return "CommandType::VIEW";
	} else 
	if(cmdType == DONE){
		return "CommandType::DONE";
	}else
    if (cmdType == STORAGE) {
		return "CommandType::STORAGE";
	} else 
	if (cmdType == EXIT_PROGRAM) {
		return "CommandType::EXIT_PROGRAM";
	} else {
		return "CommandType::INVALID";
	}
}

std::string CommandType::getFirstWord(std::string userCmd) {
	std::istringstream iss(userCmd);
	std::string firstWord;
	iss >> firstWord;
	return firstWord;
}
