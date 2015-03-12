#include "StorageCmd.h"
#include "Storage.h"

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
    Storage *storage = Storage::getInstance();
    std::string headerText;

    if (_isChangeLoc) {
        storage->setStorageLoc(_fileLoc);
        headerText = "Your todo list data storage location has been changed to "
            + _fileLoc + "\n" + 
            "The file at the previous location has been moved to the new location.\n";
    } else {
        std::string storageLoc = storage->getStorageLoc();
        headerText = "Your todo list data is currently saved at " + 
            storageLoc + "\n";
    }

    UIObject uiObj;
    uiObj.setHeaderText(headerText);

    Storage::resetInstance();
    return uiObj;
}

