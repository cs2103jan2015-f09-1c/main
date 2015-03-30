#include "TaskStub.h"
#include <iomanip> // put_time
#include <sstream>

std::string TaskStub::timetToString(time_t timing) {
    //refer to std::put_time fmt
    tm tmstruct;
    localtime_s(&tmstruct, &timing);
    std::ostringstream oss;
    oss << std::put_time(&tmstruct, "%d/%m/%y %I:%M %p");
    return oss.str();
}
time_t TaskStub::getSampleTime() {
    time_t rawTime;
    tm sampleTime;
    sampleTime.tm_hour = 7;
    sampleTime.tm_isdst = 0;
    sampleTime.tm_mday = 9;
    sampleTime.tm_min = 23;
    sampleTime.tm_mon = 2;
    sampleTime.tm_sec = 45;
    sampleTime.tm_wday = 1;
    sampleTime.tm_yday = 67;
    sampleTime.tm_year = 115;
           
    rawTime = mktime(&sampleTime);
    return rawTime;
}

Task TaskStub::getSampleTask1() {
    Task task;
    task.setTaskID((unsigned) 1);
    task.setTaskName("cs2103 tutorial");
    task.setTaskBegin(getSampleTime());
    task.setTaskEnd(getSampleTime() + 5400);
    return task;
}

Task TaskStub::getSampleTask2() {
    Task task;
    task.setTaskID((unsigned) 3);
    task.setTaskName("Performance @ UCC");
    task.setTaskBegin(getSampleTime() - 180000);
    task.setTaskEnd(getSampleTime() - 172800);
    task.markDone();
    return task;
}

Task TaskStub::getSampleTask3() {
    Task task;
    task.setTaskID((unsigned) 4);
    task.setTaskName("Buy gift for John");
    task.markDone();
    return task;
}

Task TaskStub::getSampleTask4() {
    Task task;
    task.setTaskID((unsigned) 5);
    task.setTaskName("Go to NTU");
    task.setTaskBegin(getSampleTime() - 72000);
    task.setTaskEnd(getSampleTime() - 63000);
    return task;
}

TaskStub::TaskStub(void) {
}


TaskStub::~TaskStub(void) {
}

TaskList TaskStub::getSampleTaskList() {
    TaskList list;
    list.add(getSampleTask3());
    list.add(getSampleTask1());
    list.add(getSampleTask2());
    list.add(getSampleTask4());
    return list;
}