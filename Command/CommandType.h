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
	static std::string cmdToString(Command cmdType);

private:
    static std::string getFirstWord(std::string userCmd);

};

