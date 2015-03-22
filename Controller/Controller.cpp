#include <sstream>
#include "Controller.h"
#include "CommandType.h"
#include "Interpreter.h"
#include "Storage.h"
#include "Logger.h"
#include "AddCmd.h"
#include "EditCmd.h"
#include "StorageCmd.h"
#include "DeleteCmd.h"
#include "SearchCmd.h"

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
        case CommandType::DELETE: {
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
        case CommandType::POSTPONE: {
            Logger::log("begin postpone command");

            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::UNDO: {
            Logger::log("begin undo command");

            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::SEARCH: {
            Logger::log("begin search command");

            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::VIEW: {
            Logger::log("begin view command");

            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::BLOCK: {
            Logger::log("begin block command");

            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::CONFIRM: {
            Logger::log("begin confirm command");

            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::STORAGE: {
            Logger::log("begin storage command");

            StorageCmd storageCmdObj;
            std::string cmdDetails = Interpreter::parseStoreCmd(input);
            storageCmdObj.cmdType(cmdDetails);
            return storageCmdObj.execute();
        }
        case CommandType::EXIT_PROGRAM: {
            Logger::log("============= exit program =============");

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
