#pragma once
#include <fstream>

class StorageUtils {
public:
    StorageUtils(void);
    ~StorageUtils(void);
    static bool isFileExist(const char *fileName);
    static void backupExistingFiles();
    static void restoreExistingFiles();
    static void createSettingsFile(std::string contents);
    static void removeTaskListFile(std::string path);
    static void removeSettingsFile();
    static std::string readFile(std::string filepath);
};

