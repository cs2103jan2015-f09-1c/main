//@Seow Yan Yi A0086626W
#include <assert.h>
#include "StorageCmd.h"
#include "Storage.h"
#include "InvalidFilePathException.h"
#include "Shlwapi.h" // PathFileExists
#include "History.h"
#include "State.h"
#include "MCLogger.h"
#include "TextUI.h"

bool StorageCmd::isGetLoc() const {
	return _cmdDetail == "getLocation";
}

bool StorageCmd::isHelp() const {
	return _cmdDetail == "help";
}

void StorageCmd::changeStorageLoc(std::string newStorageLoc) {
	verifyFilePath(newStorageLoc);  
	Storage *storage = Storage::getInstance();
	storage->setStorageLoc(newStorageLoc);
}


std::string StorageCmd::readStorageLoc() {
    Storage *storage = Storage::getInstance();
    std::string storageLoc = storage->getStorageLoc();
    std::string statusText = "Your todo list data is currently saved at " + 
    storageLoc + "\n";

    return statusText;
}

UIObject StorageCmd::getHelp() const {
	std::string title = "***************** COMMAND HELP: STORAGE  *****************\n\n";

	std::string intro = "The storage command allows you to view the current storage"; 
	intro = intro + " location\nof your saved tasks and also to change this storage location.\n\n";

	std::string pt1 = "1. This command can be invoked by typing \"storage\".\n";
	pt1 = pt1 + "Aliases: store\n\n";

	std::string pt2 = "2. To view the current storage location, type \"location\" after the command.\n";
	pt2 = pt2 + "Aliases: loc\nExample: storage location\n\n";

	std::string pt3 = "3. To change the location, enter a valid folder location after the command.\n";
	pt3 = pt3 + "Example: storage C:/Users/Jim/Desktop/\n\n";


	UIObject helpObj;
	helpObj.setHeaderText(title + intro + pt1 + pt2 + pt3);
	return helpObj;
}

UIObject StorageCmd::getLocation() {
	std::string location = readStorageLoc();    
	UIObject locationUI;
	locationUI.setHeaderText(location);
	return locationUI;
}

UIObject StorageCmd::changeLocation() {
	// save the previous location before it is changed
	Storage *storage = Storage::getInstance();
	std::string prevLoc = storage->getStorageLoc();

	std::string newStorageLoc = _cmdDetail;
	if (missingSlash(newStorageLoc)) {
		appendSlash(newStorageLoc);
	}

	std::string statusText;
	try {
		changeStorageLoc(newStorageLoc);
		// only record after location successfully changed
		recordInHistory(prevLoc);
		statusText = "Your todo list data storage location has been changed to:\n" +
			newStorageLoc + "\n" + 
			"The file at the previous location has been moved to the new location.";
	}  catch (InvalidFilePathException& e) {
		statusText = e.what();
	}

	UIObject locChanged;
	locChanged.setHeaderText(statusText);
	return locChanged;
}

void StorageCmd::restorePreviousLoc(std::string prevLoc) {
    changeStorageLoc(prevLoc);
}

void StorageCmd::verifyFilePath(std::string filePath) {
  int retVal = PathFileExists(filePath.c_str());
    if (retVal != 1) {
        throw InvalidFilePathException("Invalid file path. Please try again.");
    }
}

bool StorageCmd::missingSlash(std::string newStorageLoc) {
    if (_cmdDetail.back() != '\\' && _cmdDetail.back() != '/') {
        return true;
    }

    return false;
}

void StorageCmd::appendSlash(std::string &str) {
    str = str + '\\';
}

void StorageCmd::recordInHistory(std::string prevLoc) {
    State prevState; 
    prevState.recordStorageLoc(prevLoc);
    History *hist = History::getInstance();
    hist->saveState(prevState);
    hist->saveCommand(CommandType::STORAGE);
}

StorageCmd::StorageCmd(void) {
}


StorageCmd::~StorageCmd(void) {
}

void StorageCmd::cmdType(std::string detail) {
	_cmdDetail = detail;
}

UIObject StorageCmd::execute() {
	if (_cmdDetail == "help") {
		return getHelp();
	} 
	
	if (_cmdDetail == "getLocation") {
		return getLocation();
	}

	return changeLocation();
}

UIObject StorageCmd::undo() {
    History *hist = History::getInstance();
    CommandType::Command prevCmd = hist->getPreviousCommand();
    assert(prevCmd == CommandType::STORAGE);
    
    State prevState = hist->getPreviousState();
    std::string prevLoc = prevState.getStorageLoc();
    restorePreviousLoc(prevLoc);

    hist->clearHistory();

    UIObject undoMessage;
    std::string headerText = "Storage location changed back to " + 
        prevLoc;
    undoMessage.setHeaderText(headerText);
   
    return undoMessage;
}