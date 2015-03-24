#include <assert.h>
#include "StorageCmd.h"
#include "Storage.h"
#include "InvalidFilePathException.h"
#include "Shlwapi.h" // PathFileExists
#include "History.h"
#include "State.h"
#include "Logger.h"

void StorageCmd::verifyFilePath() {
  int retVal = PathFileExists(_fileLoc.c_str());
    if (retVal != 1) {
        throw InvalidFilePathException("Invalid file path. Please try again.");
    }
}
void StorageCmd::saveFilePath() {
    Storage *storage = Storage::getInstance();
    storage->setStorageLoc(_fileLoc);
}

bool StorageCmd::missingSlash() {
    if (_fileLoc.back() != '\\' && _fileLoc.back() != '/') {
        return true;
    }

    return false;
}

void StorageCmd::appendSlash() {
    _fileLoc = _fileLoc + '\\';
}

void StorageCmd::recordInHistory(std::string prevLoc) {
    State prevState; 
    prevState.recordStorageLoc(prevLoc);
    History *hist = History::getInstance();
    hist->saveState(prevState);
    hist->saveCommand(CommandType::STORAGE);
}

std::string StorageCmd::changeStorageLoc() {
    if (missingSlash()) {
        appendSlash();
    }

    verifyFilePath();  
    saveFilePath();

    std::string statusText;
    statusText = "Your todo list data storage location has been changed to:\n"
    + _fileLoc + "\n" + 
    "The file at the previous location has been moved to the new location.";

    return statusText;
}

std::string StorageCmd::readStorageLoc() {
    Storage *storage = Storage::getInstance();
    std::string storageLoc = storage->getStorageLoc();
    std::string statusText = "Your todo list data is currently saved at " + 
    storageLoc + "\n";

    return statusText;
}

StorageCmd::StorageCmd(void) {
}


StorageCmd::~StorageCmd(void) {
}

void StorageCmd::cmdType(std::string detail) {
    if (detail == "location") {
        _isChangeLoc = false;
    } else {
        _fileLoc = detail;
        _isChangeLoc = true;
    }
}

UIObject StorageCmd::execute() {
    std::string headerText;
  
    if (_isChangeLoc) {
        try {            
            Storage *storage = Storage::getInstance();
            std::string prevLoc = storage->getStorageLoc();

            headerText = changeStorageLoc();
            recordInHistory(prevLoc);
        } catch(InvalidFilePathException& e) {
            headerText = e.what();
        }

    } else {
        headerText = readStorageLoc();        
    }

    UIObject uiObj;
    uiObj.setHeaderText(headerText);

    return uiObj;
}

UIObject StorageCmd::undo() {
    History *hist = History::getInstance();
    State prevState = hist->getPreviousState();
    CommandType::Command prevCmd = hist->getPreviousCommand();

    assert(prevCmd == CommandType::STORAGE);
    
    std::string prevLoc = prevState.getStorageLoc();
    _fileLoc = prevLoc;
    changeStorageLoc();
    hist->clearHistory();

    UIObject undoMessage;
    std::string headerText = "Storage location changed back to " + 
        prevLoc;
    undoMessage.setHeaderText(headerText);
   
    return undoMessage;
}