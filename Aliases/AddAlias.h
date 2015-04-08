#pragma once
#include <string>

class AddAlias {
private:
	static void removeSpaces(std::string &input);

public:
	AddAlias(void);
	~AddAlias(void);
	

	// if there is nothing after the input command, it means
	// the command is trying show help messages. Return true in this case.
	static bool isHelp(std::string input);
};
