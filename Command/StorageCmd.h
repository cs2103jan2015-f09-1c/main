#pragma once
#include "CommandInterface.h"

class StorageCmd : public CommandInterface {
private:
    std::string _fileLoc;
    bool _isChangeLoc;
    // checks whether file path entered is a valid windows location
    void verifyFilePath();

    void saveFilePath();

    // checks whether filepath ends with a slash,
    // because operations using storage assumes folders end with a slash
    bool missingSlash();

    void appendSlash();

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

