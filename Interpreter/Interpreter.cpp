#include "Interpreter.h"
#include <iostream>

using namespace std; //please avoid using "using namespace std"
const size_t Interpreter::NUM_CHARS_STORAGE = 7;

Task Interpreter::parseAddCmd(std::string input) {

	Task a;

	CalEvent EventOut;
	time_t starttime, endtime;
	int year, mon, day, yday, tim1, tim2;

	parse(input, &EventOut);

	year = EventOut.year;
	mon = EventOut.month;
	day = EventOut.day;
	tim1 = EventOut.time;
	tim2 = EventOut.endtime;
	yday = 0;
	for (int i = 1; i < EventOut.month; i++)
		yday = yday + month_days(year, i);
	yday = yday + day;
	starttime = (year - 1970) * 365 * 24 * 3600 + yday * 24 * 3600 + (tim1 / 100) * 3600 + (tim1 % 100) * 60 + 232 * 3600;
	if (tim2 == -1) endtime = starttime;
	else endtime = (year - 1970) * 365 * 24 * 3600 + yday * 24 * 3600 + (tim2 / 100) * 3600 + (tim2 % 100) * 60 + 232 * 3600;

	a.setTaskBegin(starttime);
	a.setTaskEnd(endtime);
	a.setTaskName(EventOut.event);
	return a;
}

Task Interpreter::parseEditCmd(std::string input) {
	Task a;

	return a;
}

std::string Interpreter::parseStoreCmd(std::string input) {    
    std::string cmdDetails;
    if (input == "storage") { 
        return "location";
    }
    cmdDetails = input.substr(NUM_CHARS_STORAGE + 1); //+1 due to space
    //todo: check whether substr is either "location" or
    // a valid filepath

    return cmdDetails;
}

Interpreter::Interpreter(void) {
}


Interpreter::~Interpreter(void) {
}


int Interpreter::IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		return 1;
	else
		return 0;
}
//return the number of days in a particular month of year
int Interpreter::month_days(int y, int m)
{
	int mon_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (IsLeapYear(y) && m == 2)
		return 29;
	else
		return(mon_day[m - 1]);
}

void Interpreter::wDaySearch(int year, int month, int day, int *wday)
{
	int c = 0;
	float s;
	int m;
	for (m = 1; m<month; m++)
		c = c + month_days(year, m);
	c = c + day;
	s = year - 1 + (float)(year - 1) / 4 + (float)(year - 1) / 100 + (float)(year - 1) / 400 - 40 + c;
	*wday = (int)s % 7;
}


void Interpreter::Monthday(int year, int yearDay, int *pMonth, int *pDay)
//input: year,yearDay: year & nth day in a year
//output: pMonth,pDay: month day
{
	int dec;
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))  dec = 0;
	else dec = 1;
	if (yearDay >= 1 && yearDay <= 31) 	{
		*pMonth = 1;
		*pDay = yearDay;
	}
	else if (yearDay >= 32 && yearDay <= 60 - dec) {
		*pMonth = 2;
		*pDay = yearDay - 31;
	}
	else if (yearDay >= 61 - dec && yearDay <= 91 - dec){
		*pMonth = 3;
		*pDay = yearDay - (60 - dec);
	}
	else if (yearDay >= 92 - dec && yearDay <= 121 - dec){
		*pMonth = 4;
		*pDay = yearDay - (91 - dec);
	}
	else if (yearDay >= 122 - dec && yearDay <= 152 - dec){
		*pMonth = 5;
		*pDay = yearDay - (121 - dec);
	}
	else if (yearDay >= 153 - dec && yearDay <= 182 - dec){
		*pMonth = 6;
		*pDay = yearDay - (152 - dec);
	}
	else if (yearDay >= 183 - dec && yearDay <= 212 - dec){
		*pMonth = 7;
		*pDay = yearDay - (182 - dec);
	}
	else if (yearDay >= 214 - dec && yearDay <= 244 - dec){
		*pMonth = 8;
		*pDay = yearDay - (213 - dec);
	}
	else if (yearDay >= 245 - dec && yearDay <= 274 - dec){
		*pMonth = 9;
		*pDay = yearDay - (244 - dec);
	}
	else if (yearDay >= 275 - dec && yearDay <= 305 - dec){
		*pMonth = 10;
		*pDay = yearDay - (274 - dec);
	}
	else if (yearDay >= 306 - dec && yearDay <= 335 - dec){
		*pMonth = 11;
		*pDay = yearDay - (305 - dec);
	}
	else if (yearDay >= 336 - dec && yearDay <= 366 - dec) {
		*pMonth = 12;
		*pDay = yearDay - (335 - dec);
	}

}


void Interpreter::parse(string event, CalEvent *calEventOut)
{
	char week[7][10] = { "Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat" };
	int posOn, posAt, posTmr1, posTmr2, posNext, posFrom, posEvent;
	int i, j, k;
	CalEvent curEvent;

	curEvent.year = -1;
	curEvent.month = -1;
	curEvent.day = -1;
	curEvent.wday = -1;
	curEvent.time = -1;
	curEvent.endtime = -1;
	curEvent.event = "\0";

	//get time of "today"
	time_t rawtime;
	struct tm  timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	const char *cal = event.c_str();

	string cureve;
	posEvent = event.find(":", 0);
	if (posEvent != -1)
		cureve.assign(cal, 4, posEvent - 4);
	else
		cureve.assign(cal, 4, strlen(cal) - 4);
	const char *cheve = cureve.c_str();
	curEvent.event = cureve;    //´¿ÊÂ¼þ

	//deal with "next" in a command
	posNext = event.find(":next", 0);
	if (posNext != -1){
		i = posNext + 6;
		k = 0;
		char weekx[10];
		strcpy_s(weekx, "\0");
		while (i<strlen(cal)){
			if (cal[i] >= 'A' && cal[i] <= 'Z' || cal[i] >= 'a' && cal[i] <= 'z') {
				weekx[k] = cal[i];
				k++;
			}
			else if (cal[i] == ' ') {
				if (k != 0) break;
			}
			else {
				break;
			}
			i++;
		}
		string strweek;
		strweek.assign(weekx, 0, strlen(weekx));
		for (i = 0; i<7; i++){
			if (strweek.find(week[i], 0) != -1) break;
		}
		if (i == 7){
			return;
		}
		int yday, year, wday, nextwday;
		year = timeinfo.tm_year + 1900;
		yday = timeinfo.tm_yday + 1;
		wday = timeinfo.tm_wday;
		nextwday = 6 - wday + i + 1;
		if (yday <= 365 - nextwday){
			int pMonth, pDay;
			Monthday(year, yday + nextwday, &pMonth, &pDay);
			curEvent.year = year;
			curEvent.month = pMonth;
			curEvent.day = pDay;
		}
		else{
			int pMonth, pDay;
			Monthday(year + 1, yday + nextwday - 365, &pMonth, &pDay);
			curEvent.year = year + 1;
			curEvent.month = pMonth;
			curEvent.day = pDay;
		}
	}

	//deal with "from" in a command
	posFrom = event.find(":from", 0);
	if (posFrom != -1){
		i = posFrom + 6;
		k = 0;
		j = 0;
		char tmch[10], apm[2][5];
		int  tim[2];
		int num = 0;
		strcpy_s(apm[0], "am");
		strcpy_s(apm[1], "am");
		while (i<strlen(cal)) {
			if (cal[i] >= '0' && cal[i] <= '9') {
				tmch[k] = cal[i];
				k++;
			}
			else if (cal[i] == 'a' || cal[i] == 'p' || cal[i] == 'm') {
				apm[num][j] = cal[i];
				j++;
			}
			else if (cal[i] == 't' || cal[i] == '-') {
				k = 0;
				j = 0;
				tim[num] = atoi(tmch);
				num++;
			}
			else;
			i++;
		}
		tim[num] = atoi(tmch);
		for (int ii = 0; ii<2; ii++) {
			if (strcmp(apm[ii], "pm") == 0){
				if (tim[ii]>100)
					tim[ii] = tim[ii] + 1200;
				else
					tim[ii] = tim[ii] + 12;
			}
			if (tim[ii]<100) tim[ii] = tim[ii] * 100;
		}
		curEvent.year = timeinfo.tm_year + 1900;
		curEvent.month = timeinfo.tm_mon + 1;
		curEvent.day = timeinfo.tm_mday;
		curEvent.time = tim[0];
		curEvent.endtime = tim[1];
	}

	//deal with "on" in a command
	posOn = event.find(":on", 0);
	if (posOn != -1)	{
		i = posOn + 4;
		k = 0;
		char dat[3][5];
		int dmy[3];
		int num = 0;

		while (i<strlen(cal)) {
			if (cal[i] >= '0' && cal[i] <= '9') {
				dat[num][k] = cal[i];
				k++;
			}
			else if (cal[i] == '/') {
				k = 0;
				num++;
			}
			else {
				if (num != 2) {
					i++;
					continue;
				}
				else
					break;

			}
			i++;
		}
		for (i = 0; i<3; i++)
			dmy[i] = atoi(dat[i]);
		curEvent.year = dmy[2];
		curEvent.month = dmy[1];
		curEvent.day = dmy[0];
	}

	//deal with "at" in a command
	posAt = event.find(":at", 0);
	if (posAt != -1){
		i = posAt + 4;
		k = 0;
		j = 0;
		char tm[10], apm[3];
		int tmm;
		strcpy_s(apm, "am");
		while (i<strlen(cal)) {
			if (cal[i] >= '0' && cal[i] <= '9') {
				tm[k] = cal[i];
				k++;
			}
			else if (cal[i] == 'a' || cal[i] == 'p' || cal[i] == 'm') {
				apm[j] = cal[i];
				j++;
			}
			else
			if (j >= 2) break;
			i++;
		}

		tmm = atoi(tm);
		if (strcmp(apm, "pm") == 0){
			if (tmm>100)
				tmm = tmm + 1200;
			else
				tmm = tmm + 12;
		}
		if (tmm<100) tmm = tmm * 100;
		curEvent.time = tmm;
		if (posOn == -1){
			curEvent.year = timeinfo.tm_year + 1900;
			curEvent.month = timeinfo.tm_mon + 1;
			curEvent.day = timeinfo.tm_mday;
		}
	}

	//deal with "tomorrow" in a command
	posTmr1 = event.find(":tmr", 0);
	posTmr2 = event.find(":tomorrow", 0);
	if (posTmr1 != -1 || posTmr2 != -1){
		int yday, year;
		year = timeinfo.tm_year + 1900;
		yday = timeinfo.tm_yday + 1;
		if (yday == 365){
			curEvent.year = year + 1;
			curEvent.month = 1;
			curEvent.day = 1;
		}
		else{
			int pMonth, pDay;
			Monthday(year, yday + 1, &pMonth, &pDay);
			curEvent.year = year;
			curEvent.month = pMonth;
			curEvent.day = pDay;
		}
	}

	wDaySearch(curEvent.year, curEvent.month, curEvent.day, &curEvent.wday);
	*calEventOut = curEvent;
}

