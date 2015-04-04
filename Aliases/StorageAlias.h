#pragma once
#include <string>

class StorageAlias {
private:
	static void removeSpaces(std::string &input);

public:
	StorageAlias(void);
	~StorageAlias(void);
	
	static bool isGetLocation(std::string alias);

	// if there is nothing after the input command, it means
	// the command is trying show help messages. Return true in this case.
	static bool isHelp(std::string alias);
};

