//@Pham Thi Hong A0113955A
#pragma once
#include <string>

class SearchAlias {
private:
	static void removeSpaces(std::string &input);

public:
	SearchAlias(void);
	~SearchAlias(void);

	// if there is nothing after the input command, it means
	// the command is trying show help messages. Return true in this case.
	static bool isHelp(std::string alias);
};