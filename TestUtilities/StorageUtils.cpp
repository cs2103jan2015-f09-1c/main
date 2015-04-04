#include "StorageUtils.h"
#include <sstream>
StorageUtils::StorageUtils(void) {
}


StorageUtils::~StorageUtils(void) {
}

bool StorageUtils::isFileExist(const char *fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}
void StorageUtils::backupExistingFiles() {
    //copy settings.txt and tasklist.txt to safe place
    if (isFileExist("settings.txt")) {
        rename("settings.txt", "settings_backup.txt");
    }

    if (isFileExist("tasklist.txt")) {
        rename("tasklist.txt", "tasklist_backup.txt");
    }
}

void StorageUtils::restoreExistingFiles() {
    //restore original files
    if (isFileExist("settings_backup.txt")) {
        rename("settings_backup.txt", "settings.txt");
    }

    if (isFileExist("tasklist_backup.txt")) {
        rename("tasklist_backup.txt", "tasklist.txt");
    }
}

void StorageUtils::createSettingsFile(std::string contents) {
    std::ofstream writeFile("settings.txt");
    writeFile << contents;
    writeFile.close();
}
        
void StorageUtils::removeTaskListFile(std::string path) {
    std::string filename = path + "tasklist.txt";
    remove(filename.c_str());
}

void StorageUtils::removeSettingsFile() {
    remove("settings.txt");
}

std::string StorageUtils::readFile(std::string filepath) {
    std::string line;
    std::ifstream read(filepath); 
    std::ostringstream oss;
    while (std::getline(read, line)) {
        oss << line << std::endl;
    }

    return oss.str();
}