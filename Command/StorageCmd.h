//@author A0086626W
#pragma once
#include "CommandInterface.h"

class StorageCmd : public CommandInterface {
private:
    std::string _cmdDetail;

	// based on the private attribute _cmdDetail, isGetLoc() returns
	// true if the storage command should get the current storage location.
	bool isGetLoc() const;
	bool isHelp() const;

	void changeStorageLoc(std::string newStorageLoc);
	std::string readStorageLoc();

	UIObject getHelp() const;
	UIObject getLocation();
	UIObject changeLocation();

    void restorePreviousLoc(std::string prevLoc);

    // checks whether file path entered is a valid windows location
    void verifyFilePath(std::string filePath);

    // checks whether filepath ends with a slash,
    // because operations using storage assumes folders end with a slash
    bool missingSlash(std::string newStorageLoc);

	// appends a slash to the string using pass-by-reference
    void appendSlash(std::string &str);

    // saves previous storage location into history 
    // this will be used if the user wants to undo
    void recordInHistory(std::string prevLoc);

public:
    StorageCmd(void);
    ~StorageCmd(void);
    void cmdType(std::string detail);
    UIObject execute();
    UIObject undo();
};

