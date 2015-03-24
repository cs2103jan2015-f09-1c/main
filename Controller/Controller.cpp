#include <sstream>
#include <assert.h>
#include "Controller.h"
#include "Interpreter.h"
#include "Storage.h"
#include "Logger.h"
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
            Logger::log("begin add command");

            AddCmd addCmdObj;
            Task task = Interpreter::parseAddCmd(input);
            addCmdObj.prepareTask(task);
            return addCmdObj.execute();
        }
        case CommandType::DEL: {
            Logger::log("begin delete command");

            DeleteCmd delCmdObj;
            Task task = Interpreter::parseDelCmd(input);
            delCmdObj.prepareTask(task);
            return delCmdObj.execute();
        }
        case CommandType::EDIT: {
            Logger::log("begin edit command");

            EditCmd editCmdObj;
            Task task = Interpreter::parseEditCmd(input);
            editCmdObj.prepareTask(task);
            return editCmdObj.execute();
        }
        case CommandType::UNDO: {
            Logger::log("begin undo command");
            History *hist = History::getInstance();
            CommandType::Command prevCmd = hist->getPreviousCommand();
            
            UIObject feedback;
            feedback = undoCommand(prevCmd);
            return feedback;
        }
        case CommandType::SEARCH: {
            Logger::log("begin search command");

            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::VIEW: {
            Logger::log("begin view command");
			ViewCmd ViewObj;
			std::string detail = Interpreter::parseViewCmd(input);
			ViewObj.prepareDetail(detail);
			return ViewObj.execute();
        }
        case CommandType::STORAGE: {
            Logger::log("begin storage command");

            StorageCmd storageCmdObj;
            std::string cmdDetails = Interpreter::parseStoreCmd(input);
            storageCmdObj.cmdType(cmdDetails);
            return storageCmdObj.execute();
        }
        case CommandType::EXIT_PROGRAM: {
            Logger::log("============= exit program ==============");

            Storage::resetInstance();
            exit(EXIT_SUCCESS);
        }
        case CommandType::INVALID: {
            Logger::log("invalid command");
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
