#include "TaskStub.h"
#include <iomanip> // put_time
#include <sstream>



int TaskStub::_secsInADay = 86400;
int TaskStub::_secsInHalfDay = 43200;
int TaskStub::_secsInAnHour = 3600;
time_t TaskStub::_9Mar723AM = getSampleTime();
time_t TaskStub::_9Mar723PM = _9Mar723AM + _secsInHalfDay;
time_t TaskStub::_10Mar723AM = _9Mar723AM + _secsInADay;
time_t TaskStub::_10Mar723PM = _10Mar723AM + _secsInHalfDay;
time_t TaskStub::_11Mar723AM = _10Mar723AM + _secsInADay;
time_t TaskStub::_11Mar723PM = _11Mar723AM + _secsInHalfDay;

std::string TaskStub::timetToString(time_t timing) {
    //refer to std::put_time fmt
    tm tmstruct;
    localtime_s(&tmstruct, &timing);
    std::ostringstream oss;
    oss << std::put_time(&tmstruct, "%d/%m/%y %I:%M %p");
    return oss.str();
}

TaskStub::TaskStub(void) {
}


TaskStub::~TaskStub(void) {
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
    task.setTaskName("dummy T1");
    task.setTaskBegin(_9Mar723AM);
    task.setTaskEnd(_9Mar723AM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask2() {
    Task task;
    task.setTaskID((unsigned) 2);
    task.setTaskName("dummy T2");
    task.setTaskBegin(_9Mar723PM);
    task.setTaskEnd(_9Mar723PM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask3() {
    Task task;
    task.setTaskID((unsigned) 3);
    task.setTaskName("dummy T3");
    task.setTaskBegin(_9Mar723AM);
    task.setTaskEnd(_9Mar723PM);
    task.markDone();
    return task;
}

Task TaskStub::getSampleTask4() {
    Task task;
    task.setTaskID((unsigned) 4);
    task.setTaskName("dummy T4");
    task.setTaskBegin(_10Mar723AM);
    task.setTaskEnd(_10Mar723AM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask5() {
    Task task;
    task.setTaskID((unsigned) 5);
    task.setTaskName("dummy T5");
    task.setTaskBegin(_10Mar723PM);
    task.setTaskEnd(_10Mar723PM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask6() {
    Task task;
    task.setTaskID((unsigned) 6);
    task.setTaskName("dummy T6");
    task.setTaskBegin(_11Mar723AM);
    task.setTaskEnd(_11Mar723PM);
    task.markDone();
    return task;
}

Task TaskStub::getSampleTask7() {
    Task task;
    task.setTaskID((unsigned) 7);
    task.setTaskName("dummy T7");
    task.setTaskBegin(_11Mar723AM);
    task.setTaskEnd(_11Mar723PM);
    task.markDone();
    return task;
}

Task TaskStub::getSampleTask8() {
    Task task;
    task.setTaskID((unsigned) 8);
    task.setTaskName("dummy T8");
    task.setTaskBegin(_11Mar723AM);
    task.setTaskEnd(_11Mar723AM + _secsInAnHour);
    return task;
}

TaskList TaskStub::getLargeTaskList() {
    TaskList list;
    list.add(getSampleTask1());
    list.add(getSampleTask2());
    list.add(getSampleTask3());
    list.add(getSampleTask4());
    list.add(getSampleTask5());
    list.add(getSampleTask6());
    list.add(getSampleTask7());
    list.add(getSampleTask8());
    return list;
}

TaskList TaskStub::getSmallTaskList() {
    TaskList list;
    list.add(getSampleTask1());
    list.add(getSampleTask3());
    list.add(getSampleTask5());
    return list;
}