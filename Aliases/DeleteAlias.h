#pragma once
#include <string>

class DeleteAlias {
private:
	static void removeSpaces(std::string &input);

public:
	DeleteAlias(void);
	~DeleteAlias(void);
	
	static bool isInteger(std::string detail);

	// if there is nothing after the input command, it means
	// the command is trying show help messages. Return true in this case.
	static bool isHelp(std::string alias);
};