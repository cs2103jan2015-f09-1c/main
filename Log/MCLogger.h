//@Seow Yan Yi A0086626W
#pragma once
#include <string>

class MCLogger {
private:
    static void writeToLog(std::string msg);
    static std::string getDateTime();
public:
    static void log(std::string msg);
    MCLogger(void);
    ~MCLogger(void);
};

