#include "CommandType.h"
#include <algorithm>

CommandType::CommandType(void) {
}

CommandType::~CommandType(void) {
}

CommandType::Command CommandType::determineCmdType(std::string userCmd) {
    std::string cmdString = getFirstWord(userCmd);

	if (isAdd(cmdString)) {
		return CommandType::ADD;
	} else
	if (isDel(cmdString)) {
		return CommandType::DEL;
	} else
	if (isEdit(cmdString)) {
		return CommandType::EDIT;
	} else
	if (isUndo(cmdString)) {
		return CommandType::UNDO;
	} else
	if (isSearch(cmdString)) {
		return CommandType::SEARCH;
	} else
	if (isView(cmdString)) {
		return CommandType::VIEW;
	} else 
	if(isDone(cmdString)){
		return CommandType::DONE;
	}else
    if (isStorage(cmdString)) {
		return CommandType::STORAGE;
	} else 
	if (isExit(cmdString)) {
		return CommandType::EXIT_PROGRAM;
	} else {
		return CommandType::INVALID;
	}
}

std::string CommandType::filterOutCmd(std::string input) {
	int firstWordLength = getFirstWord(input).length();
	return input.substr(firstWordLength);
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

bool CommandType::isAdd(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "add"; //|| cmd == "a";
}

bool CommandType::isDel(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "delete"; // || cmd == "del";
}

bool CommandType::isEdit(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "edit";// || cmd == "ed" || cmd == "e";
}

bool CommandType::isUndo(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "undo";// || cmd == "un" || cmd == "u";
}

bool CommandType::isSearch(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "search";// || cmd == "se" || cmd == "s";
}

bool CommandType::isView(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "view";// || cmd == "v";
}

bool CommandType::isDone(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "done";// || cmd == "d" || cmd == "mark" || cmd == "m";
}

bool CommandType::isStorage(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "storage" || cmd == "store";
}

bool CommandType::isExit(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "exit";// || cmd == "ex" || cmd == "x" || cmd == "quit" || cmd == "q";
}
