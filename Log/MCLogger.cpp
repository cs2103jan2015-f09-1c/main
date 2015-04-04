#include "MCLogger.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip> //put_time

void MCLogger::writeToLog(std::string msg) {
	std::ofstream writeFile("MyCalLog.txt", std::ios::app);
	writeFile << msg << std::endl;
	writeFile.close();
}

std::string MCLogger::getDateTime() {
    time_t curTime;
    time(&curTime); 
    tm tmstruct;
    localtime_s(&tmstruct, &curTime);
    std::ostringstream oss;
    oss << std::put_time(&tmstruct, "[%d/%m/%y %I:%M:%S %p]   ");

    return oss.str();
}

void MCLogger::log(std::string msg) {
    std::string curTime = getDateTime();
    msg = curTime + msg;
    writeToLog(msg);
}

MCLogger::MCLogger(void) {
}


MCLogger::~MCLogger(void) {
}
