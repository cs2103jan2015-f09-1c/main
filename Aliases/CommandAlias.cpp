#include "CommandAlias.h"
#include <algorithm> //std::transform

CommandAlias::CommandAlias(void) {
}


CommandAlias::~CommandAlias(void) {
}

bool CommandAlias::isAdd(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "add"; //|| cmd == "a";
}

bool CommandAlias::isDel(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "delete"; // || cmd == "del";
}

bool CommandAlias::isEdit(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "edit";// || cmd == "ed" || cmd == "e";
}

bool CommandAlias::isUndo(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "undo";// || cmd == "un" || cmd == "u";
}

bool CommandAlias::isSearch(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "search";// || cmd == "se" || cmd == "s";
}

bool CommandAlias::isView(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "view";// || cmd == "v";
}

bool CommandAlias::isDone(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "done";// || cmd == "d" || cmd == "mark" || cmd == "m";
}

bool CommandAlias::isStorage(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "storage" || cmd == "store";
}

bool CommandAlias::isExit(std::string cmd) {
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
	return cmd == "exit";// || cmd == "ex" || cmd == "x" || cmd == "quit" || cmd == "q";
}
