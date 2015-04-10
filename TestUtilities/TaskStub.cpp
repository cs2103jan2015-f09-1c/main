#include "TaskStub.h"
#include <iomanip> // put_time
#include <sstream>

int TaskStub::_secsInADay = 86400;
int TaskStub::_secsInHalfDay = 43200;
int TaskStub::_secsInAnHour = 3600;
int TaskStub::_secsInThreeDays = 259200;
time_t TaskStub::_9Mar723AM = getSampleTime();
time_t TaskStub::_9Mar723PM = _9Mar723AM + _secsInHalfDay;
time_t TaskStub::_10Mar723AM = _9Mar723AM + _secsInADay;
time_t TaskStub::_10Mar723PM = _10Mar723AM + _secsInHalfDay;
time_t TaskStub::_11Mar723AM = _10Mar723AM + _secsInADay;
time_t TaskStub::_11Mar723PM = _11Mar723AM + _secsInHalfDay;
time_t TaskStub::_6Apr9AM = getSampleTimeApr();
time_t TaskStub::_7Apr9AM = _6Apr9AM + _secsInADay;
time_t TaskStub::_8Apr9AM = _7Apr9AM + _secsInADay;
time_t TaskStub::_9Apr9AM = _8Apr9AM + _secsInADay;
time_t TaskStub::_10Apr9AM = _9Apr9AM + _secsInADay;
time_t TaskStub::_12Apr9AM = _10Apr9AM + 2*_secsInADay;
time_t TaskStub::_13Apr9AM = _12Apr9AM + _secsInADay;
time_t TaskStub::_14Apr9AM = _13Apr9AM + _secsInADay;
time_t TaskStub::_15Apr9AM = _14Apr9AM + _secsInADay;
time_t TaskStub::_16Apr9AM = _15Apr9AM + _secsInADay;
time_t TaskStub::_17Apr9AM = _16Apr9AM + _secsInADay;
time_t TaskStub::_19Apr9AM = _17Apr9AM + 2*_secsInADay;
time_t TaskStub::_Today9AM = getCurrentTime();
time_t TaskStub::_Tomorrow9AM = _Today9AM+ _secsInADay;

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

time_t TaskStub::getSampleTimeApr() {
    time_t rawTime;
    tm sampleTime;
    sampleTime.tm_hour = 9;
    sampleTime.tm_isdst = 0;
    sampleTime.tm_mday = 6;
    sampleTime.tm_min = 0;
    sampleTime.tm_mon = 3;
    sampleTime.tm_sec = 45;
    sampleTime.tm_wday = 2;
    sampleTime.tm_yday = 96;
    sampleTime.tm_year = 115;
           
    rawTime = mktime(&sampleTime);
    return rawTime;
}

time_t TaskStub::getCurrentTime() {
	time_t rawtime;
	time(&rawtime);
    return rawtime;
}

std::string TaskStub::getCurrentDate() {
    time_t curTime = getCurrentTime();
    tm dateStruct;
    localtime_s(&dateStruct, &curTime);
    std::ostringstream beginOss;
    beginOss << std::put_time(&dateStruct, "%a %b %d %Y");
    return beginOss.str();
}

std::string TaskStub::getTomorrowDate() {
    time_t curTime = getCurrentTime() + _secsInADay;
    tm dateStruct;
    localtime_s(&dateStruct, &curTime);
    std::ostringstream beginOss;
    beginOss << std::put_time(&dateStruct, "%a %b %d %Y");
    return beginOss.str();
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
    task.setTaskBegin(_9Mar723AM);
    task.setTaskEnd(_9Mar723PM);
    task.markDone();
    return task;
}

Task TaskStub::getSampleTask3() {
    Task task;
    task.setTaskID((unsigned) 3);
    task.setTaskName("dummy T3");
    task.setTaskBegin(_9Mar723PM);
    task.setTaskEnd(_9Mar723PM + _secsInAnHour);
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

Task TaskStub::getSampleTask9() {
    Task task;
    task.setTaskID((unsigned) 9);
    task.setTaskName("dummy T9");
    task.setTaskBegin(_6Apr9AM);
    task.setTaskEnd(_6Apr9AM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask10() {
    Task task;
    task.setTaskID((unsigned) 10);
    task.setTaskName("dummy T10");
    task.setTaskBegin(_7Apr9AM);
    task.setTaskEnd(_7Apr9AM + _secsInHalfDay);
    return task;
}

Task TaskStub::getSampleTask11() {
    Task task;
    task.setTaskID((unsigned) 11);
    task.setTaskName("dummy T11");
    task.setTaskBegin(_8Apr9AM);
    task.setTaskEnd(_8Apr9AM + _secsInHalfDay);
    return task;
}

Task TaskStub::getSampleTask12() {
    Task task;
    task.setTaskID((unsigned) 12);
    task.setTaskName("dummy T12");
    task.setTaskBegin(_9Apr9AM);
    task.setTaskEnd(_9Apr9AM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask13() {
    Task task;
    task.setTaskID((unsigned) 13);
    task.setTaskName("dummy T13");
    task.setTaskBegin(_10Apr9AM);
    task.setTaskEnd(_10Apr9AM + _secsInHalfDay);
    return task;
}


Task TaskStub::getSampleTask14() {
    Task task;
    task.setTaskID((unsigned) 14);
    task.setTaskName("dummy T14");
    task.setTaskBegin(_10Apr9AM);
    task.setTaskEnd(_10Apr9AM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask15() {
    Task task;
    task.setTaskID((unsigned) 15);
    task.setTaskName("dummy T15");
    task.setTaskBegin(_12Apr9AM);
    task.setTaskEnd(_12Apr9AM + _secsInHalfDay);
    return task;
}

Task TaskStub::getSampleTask16() {
    Task task;
    task.setTaskID((unsigned) 16);
    task.setTaskName("dummy T16");
    task.setTaskBegin(_13Apr9AM);
    task.setTaskEnd(_13Apr9AM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask17() {
    Task task;
    task.setTaskID((unsigned) 17);
    task.setTaskName("dummy T17");
    task.setTaskBegin(_14Apr9AM);
    task.setTaskEnd(_14Apr9AM + _secsInHalfDay);
    return task;
}

Task TaskStub::getSampleTask18() {
    Task task;
    task.setTaskID((unsigned) 18);
    task.setTaskName("dummy T18");
    task.setTaskBegin(_15Apr9AM);
    task.setTaskEnd(_15Apr9AM + _secsInHalfDay);
    return task;
}

Task TaskStub::getSampleTask19() {
    Task task;
    task.setTaskID((unsigned) 19);
    task.setTaskName("dummy T19");
    task.setTaskBegin(_16Apr9AM);
    task.setTaskEnd(_16Apr9AM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask20() {
    Task task;
    task.setTaskID((unsigned) 20);
    task.setTaskName("dummy T20");
    task.setTaskBegin(_16Apr9AM);
    task.setTaskEnd(_16Apr9AM + _secsInHalfDay);
    return task;
}


Task TaskStub::getSampleTask21() {
    Task task;
    task.setTaskID((unsigned) 21);
    task.setTaskName("dummy T21");
    task.setTaskBegin(_17Apr9AM);
    task.setTaskEnd(_17Apr9AM + _secsInAnHour);
    return task;
}

Task TaskStub::getSampleTask22() {
    Task task;
    task.setTaskID((unsigned) 22);
    task.setTaskName("dummy T22");
    task.setTaskBegin(_19Apr9AM);
    task.setTaskEnd(_19Apr9AM + _secsInHalfDay);
    return task;
}

Task TaskStub::getSampleTask23() {
    Task task;
    task.setTaskID((unsigned) 23);
    task.setTaskName("dummy T23");
    task.setTaskBegin(_Today9AM);
    task.setTaskEnd(_Today9AM + _secsInHalfDay);
    return task;
}

Task TaskStub::getSampleTask24() {
    Task task;
    task.setTaskID((unsigned) 24);
    task.setTaskName("dummy T24");
    task.setTaskBegin(_Tomorrow9AM);
    task.setTaskEnd(_Tomorrow9AM + _secsInHalfDay);
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

TaskList TaskStub::getAprTaskList() {
    TaskList list;
    list.add(getSampleTask9());
    list.add(getSampleTask10());
    list.add(getSampleTask11());
    list.add(getSampleTask12());
    list.add(getSampleTask13());
    list.add(getSampleTask14());
    list.add(getSampleTask15());
	list.add(getSampleTask16());
    list.add(getSampleTask17());
    list.add(getSampleTask18());
    list.add(getSampleTask19());
    list.add(getSampleTask20());
    list.add(getSampleTask21());
    list.add(getSampleTask22());
    return list;
}

TaskList TaskStub::getCurrentTaskList() {
    TaskList list;
    list.add(getSampleTask23());
	list.add(getSampleTask24());
	return list;
}

