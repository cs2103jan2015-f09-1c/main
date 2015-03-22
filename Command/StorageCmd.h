#pragma once
#include "CommandInterface.h"

class StorageCmd : public CommandInterface {
private:
    std::string _fileLoc;
    bool _isChangeLoc;
    // saves previous storage location into history 
    // this will be used if the user wants to undo
    void recordInHistory(std::string prevLoc);
    std::string changeStorageLoc();
    std::string readStorageLoc();

public:
    StorageCmd(void);
    ~StorageCmd(void);
    void cmdType(std::string detail);
    UIObject execute();
    UIObject undo();
};

