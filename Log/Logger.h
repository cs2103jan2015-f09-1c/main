#pragma once
#include <string>

class Logger {
private:
    static void writeToLog(std::string msg);
    static std::string getDateTime();
public:
    static void log(std::string msg);
    Logger(void);
    ~Logger(void);
};

