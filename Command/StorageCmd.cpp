#include "StorageCmd.h"
#include "Storage.h"
#include "InvalidFilePathException.h"
#include "Shlwapi.h" // PathFileExists

std::string StorageCmd::changeStorageLoc() {
    Storage *storage = Storage::getInstance();
    std::string statusText;

    try {
        int retVal = PathFileExists(_fileLoc.c_str());
        if (retVal != 1) {
            throw InvalidFilePathException("Invalid file path. Please try again.");
        }

        storage->setStorageLoc(_fileLoc);
        statusText = "Your todo list data storage location has been changed to:\n"
        + _fileLoc + "\n" + 
        "The file at the previous location has been moved to the new location.";
    } catch(InvalidFilePathException& e) {
        statusText = e.what();
    }

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
        headerText = changeStorageLoc();
    } else {
        headerText = readStorageLoc();        
    }

    UIObject uiObj;
    uiObj.setHeaderText(headerText);

    return uiObj;
}

