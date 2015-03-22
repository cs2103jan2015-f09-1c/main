#include <sstream>
#include "Controller.h"
#include "CommandType.h"
#include "Interpreter.h"
#include "Storage.h"
#include "AddCmd.h"
#include "EditCmd.h"
#include "StorageCmd.h"
#include "DeleteCmd.h"
#include "SearchCmd.h"

UIObject Controller::handleInput(std::string input) {
    CommandType::Command cmdType = CommandType::determineCmdType(input);  
    switch (cmdType) {
        case CommandType::ADD: {
            AddCmd addCmdObj;
            Task task = Interpreter::parseAddCmd(input);
            addCmdObj.prepareTask(task);
            return addCmdObj.execute();
        }
        case CommandType::DELETE: {
            DeleteCmd delCmdObj;
            Task task = Interpreter::parseDelCmd(input);
            delCmdObj.prepareTask(task);
            return delCmdObj.execute();
        }
        case CommandType::EDIT: {
            EditCmd editCmdObj;
            Task task = Interpreter::parseEditCmd(input);
            editCmdObj.prepareTask(task);
            return editCmdObj.execute();
        }
        case CommandType::POSTPONE: {
            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::UNDO: {
            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::SEARCH: {
            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::VIEW: {
            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::BLOCK: {
            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::CONFIRM: {
            UIObject inProgress;
            inProgress.setHeaderText("This feature is work in progress");
            return inProgress;
        }
        case CommandType::STORAGE: {
            StorageCmd storageCmdObj;
            std::string cmdDetails = Interpreter::parseStoreCmd(input);
            storageCmdObj.cmdType(cmdDetails);
            return storageCmdObj.execute();
        }
        case CommandType::EXIT_PROGRAM: {
            Storage::resetInstance();
            exit(EXIT_SUCCESS);
        }
        case CommandType::INVALID: {
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
