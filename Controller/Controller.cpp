#include <sstream>
#include <assert.h>
#include "Controller.h"
#include "Interpreter.h"
#include "Storage.h"
#include "MCLogger.h"
#include "AddCmd.h"
#include "EditCmd.h"
#include "StorageCmd.h"
#include "DeleteCmd.h"
#include "SearchCmd.h"
#include "DoneCmd.h"
#include "ViewCmd.h"
#include "History.h"
#include "TaskNotFoundException.h"
#include "InvalidInputException.h"
//#include "HelpCmd.h"


UIObject Controller::undoCommand(CommandType::Command cmdType) {
    switch (cmdType) { 
        case CommandType::ADD: {
            AddCmd addCmd;
            return addCmd.undo();
        }
        case CommandType::DEL: {
            DeleteCmd delCmd;
            return delCmd.undo();
        }
        case CommandType::EDIT: {
            StorageCmd editCmd;
            return editCmd.undo();
        }
		case CommandType::DONE: {
            DoneCmd doneCmd;
            return doneCmd.undo();
        }
        case CommandType::STORAGE: {
            StorageCmd storageCmd;
            return storageCmd.undo();
        }
        default:
            UIObject noUndo;
            noUndo.setHeaderText("No more actions to undo.");
            return noUndo;
    }
}

UIObject Controller::handleInput(std::string input) {
    CommandType::Command cmdType = CommandType::determineCmdType(input);  
	std::string filteredCmd = CommandType::filterOutCmd(input);

    switch (cmdType) {
        case CommandType::ADD: {
            MCLogger::log("Controller.cpp: begin add command");

            AddCmd addCmdObj;
            Task task = Interpreter::parseAddCmd(input);
            addCmdObj.prepareTask(task);
            return addCmdObj.execute();
        }
        case CommandType::DEL: {
            MCLogger::log("Controller.cpp: begin delete command");

            DeleteCmd delCmdObj;
            int TaskId = Interpreter::parseDelCmd(filteredCmd);
            delCmdObj.prepareTaskId(TaskId);
            return delCmdObj.execute();
        }
        case CommandType::EDIT: {
            MCLogger::log("Controller.cpp: begin edit command");
            try {
                EditCmd editCmdObj;
                Task task = Interpreter::parseEditCmd(input);
                editCmdObj.prepareTask(task);
                return editCmdObj.execute();
            } catch (TaskNotFoundException &e) {
                UIObject notFound;
                notFound.setHeaderText(e.what());
                return notFound;
            } catch (InvalidInputException &e) {
                UIObject invalidInput;
                invalidInput.setHeaderText(e.what());
                return invalidInput;
            }
        }
        case CommandType::UNDO: {
            MCLogger::log("Controller.cpp: begin undo command");
            History *hist = History::getInstance();
            CommandType::Command prevCmd = hist->getPreviousCommand();
            
            UIObject feedback;
            feedback = undoCommand(prevCmd);
            return feedback;
        }
        case CommandType::SEARCH: {
            MCLogger::log("Controller.cpp: begin search command");

			SearchCmd SearchCmdObj;
			TaskList::TList List = Interpreter::parseSearchCmd(filteredCmd);
			SearchCmdObj.prepareList(List);
			return SearchCmdObj.execute();
        }
        case CommandType::VIEW: {
            MCLogger::log("Controller.cpp: begin view command");
			ViewCmd ViewObj;
			std::string detail = Interpreter::parseViewCmd(filteredCmd);
			ViewObj.prepareDetail(detail);
			return ViewObj.execute();
        }
        case CommandType::STORAGE: {
            MCLogger::log("Controller.cpp: begin storage command");
            std::string parsedCmd = Interpreter::parseStoreCmd(filteredCmd);
			StorageCmd storageCmdObj;
            storageCmdObj.cmdType(parsedCmd);
            return storageCmdObj.execute();
        }    
		case CommandType::DONE: {
            MCLogger::log("Controller.cpp: begin done command");
            DoneCmd doneCmdObj;
			int noOfChars = CommandType:: getNumOfChars(input);
            int taskId = Interpreter::parseDoneCmd(filteredCmd);
			doneCmdObj.prepareTaskId(taskId);
            return doneCmdObj.execute();
        }/*
		case CommandType::HELP: {
            MCLogger::log("Controller.cpp: begin help command");
            HelpCmd helpCmdObj;
            return helpCmdObj.execute();
        }*/
        case CommandType::EXIT_PROGRAM: {
            MCLogger::log("============= exit program ==============");
            Storage::resetInstance();
			MappingNumber::resetInstance();
			History::resetInstance();

            exit(EXIT_SUCCESS);
        }
        case CommandType::INVALID: {
            MCLogger::log("Controller.cpp: invalid command");
            UIObject invalidCmd;
            invalidCmd.setHeaderText("The command entered \"" + input + "\" is invalid.");
            return invalidCmd;
        }
        default: {
			MCLogger::log("ERROR: UNRECOGNIZED COMMAND TYPE");
            assert(false);
            UIObject invalidCmd;
            invalidCmd.setHeaderText("The command entered is invalid.");
            return invalidCmd;
        }
    }
}

Controller::Controller(void) {
}


Controller::~Controller(void) {
}
