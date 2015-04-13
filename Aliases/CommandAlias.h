//@Seow Yan Yi A0086626W
#pragma once
#include <string>

class CommandAlias {
public:
	CommandAlias(void);
	~CommandAlias(void);

	// the following isAdd, isDel ... isExit methods returns true if "cmd" matches 
	// one of the allowed aliases for the corresponding command
	static bool isAdd(std::string cmd);
	static bool isDel(std::string cmd);
	static bool isEdit(std::string cmd);
	static bool isUndo(std::string cmd);
	static bool isSearch(std::string cmd);
	static bool isView(std::string cmd);
	static bool isDone(std::string cmd);
	static bool isStorage(std::string cmd);
	static bool isExit(std::string cmd);
};

