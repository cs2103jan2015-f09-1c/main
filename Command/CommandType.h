#pragma once
#include <string>
#include <sstream>

class CommandType {
public:
    enum Command {
	    ADD, DEL, EDIT, UNDO, 
	    SEARCH, VIEW, DONE,
	    STORAGE,
	    EXIT_PROGRAM, INVALID
    };

    CommandType(void);
    ~CommandType(void);

    static Command determineCmdType(std::string userCmd);

	// returns the details of the command without the actual command itself
	static std::string filterOutCmd(std::string input);

	// returns the number of characters the command has. This is used by the 
	// interpreter for parsing the subsequent details of the command.
	static int getNumOfChars(std::string userCmd);

	// given a command type, cmdToString returns a string representation
	// of the command. Used for logging/debugging purposes.
	static std::string cmdToString(Command cmdType);

private:
    static std::string getFirstWord(std::string input);

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

