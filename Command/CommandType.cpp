//@Seow Yan Yi A0086626W
#include "CommandType.h"
#include "CommandAlias.h"
#include <iostream>
CommandType::CommandType(void) {
}

CommandType::~CommandType(void) {
}

CommandType::Command CommandType::determineCmdType(std::string userCmd) {
    std::string cmdString = getFirstWord(userCmd);

	if (CommandAlias::isAdd(cmdString)) {
		return CommandType::ADD;
	} else
	if (CommandAlias::isDel(cmdString)) {
		return CommandType::DEL;
	} else
	if (CommandAlias::isEdit(cmdString)) {
		return CommandType::EDIT;
	} else
	if (CommandAlias::isUndo(cmdString)) {
		return CommandType::UNDO;
	} else
	if (CommandAlias::isSearch(cmdString)) {
		return CommandType::SEARCH;
	} else
	if (CommandAlias::isView(cmdString)) {
		return CommandType::VIEW;
	} else 
	if(CommandAlias::isDone(cmdString)){
		return CommandType::DONE;
	}else
    if (CommandAlias::isStorage(cmdString)) {
		return CommandType::STORAGE;
	} else 
	if (CommandAlias::isExit(cmdString)) {
		return CommandType::EXIT_PROGRAM;
	} else {
		return CommandType::INVALID;
	}
}

std::string CommandType::filterOutCmd(std::string input) {
	size_t firstWordLength = getFirstWord(input).length();

	if (input.length() > firstWordLength) {
		return input.substr(firstWordLength + 1);
	}

	// only one word in input string.
	return "";
}

int CommandType::getNumOfChars(std::string userCmd) {
	std::string cmdString = getFirstWord(userCmd);
	return cmdString.length();
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

std::string CommandType::getFirstWord(std::string input) {
	std::istringstream iss(input);
	std::string firstWord;
	iss >> firstWord;
	return firstWord;
}