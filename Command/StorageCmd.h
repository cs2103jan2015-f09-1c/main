#pragma once
#include "CommandInterface.h"

class StorageCmd : public CommandInterface {
private:
    std::string _fileLoc;
    bool _isChangeLoc;
    std::string changeStorageLoc();
    std::string readStorageLoc();

public:
    StorageCmd(void);
    ~StorageCmd(void);
    void cmdType(std::string detail);
    UIObject execute();
    UIObject undo();
};

