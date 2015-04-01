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
        case CommandType::STORAGE: {
            StorageCmd storageCmd;
            return storageCmd.undo();
        }
		case CommandType::DONE:{
            DoneCmd doneCmd;
            return doneCmd.undo();
        }
        default:
            UIObject noUndo;
            noUndo.setHeaderText("No more actions to undo.");
            return noUndo;
    }
}

UIObject Controller::handleInput(std::string input) {
    CommandType::Command cmdType = CommandType::determineCmdType(input);  
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
            int TaskId = Interpreter::parseDelCmd(input);
            delCmdObj.prepareTaskId(TaskId);
            return delCmdObj.execute();
        }
        case CommandType::EDIT: {
            MCLogger::log("Controller.cpp: begin edit command");

            EditCmd editCmdObj;
            Task task = Interpreter::parseEditCmd(input);
            editCmdObj.prepareTask(task);
            return editCmdObj.execute();
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
			TaskList::TList List = Interpreter::parseSearchCmd(input);
			SearchCmdObj.prepareList(List);
			return SearchCmdObj.execute();
        }
        case CommandType::VIEW: {
            MCLogger::log("Controller.cpp: begin view command");
			ViewCmd ViewObj;
			std::string detail = Interpreter::parseViewCmd(input);
			ViewObj.prepareDetail(detail);
			return ViewObj.execute();
        }
        case CommandType::STORAGE: {
            MCLogger::log("Controller.cpp: begin storage command");

            StorageCmd storageCmdObj;
            std::string cmdDetails = Interpreter::parseStoreCmd(input);
            storageCmdObj.cmdType(cmdDetails);
            return storageCmdObj.execute();
        }    
		case CommandType::DONE: {
            MCLogger::log("Controller.cpp: begin done command");

            DoneCmd doneCmdObj;
            int index = Interpreter::parseDoneCmd(input);
			doneCmdObj.prepareIndex(index);
            return doneCmdObj.execute();
        }
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
            invalidCmd.setHeaderText("The command entered is invalid.");
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
