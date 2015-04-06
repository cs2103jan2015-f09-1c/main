#include "ViewType.h"
#include <sstream>
#include <algorithm>

ViewType::ViewType(void) {
}

ViewType::~ViewType(void) {
}

ViewType::View ViewType::determineViewType(std::string _detail){
	std::transform(_detail.begin(), _detail.end(), _detail.begin(), ::tolower);
	if (_detail == "sunday") {
		return ViewType::SUNDAY;
	} else
	if (_detail == "monday") {
		return ViewType::MONDAY;
	} else
	if (_detail == "tuesday") {
		return ViewType::TUESDAY;
	} else
	if (_detail == "wednesday") {
		return ViewType::WEDNESDAY;
	} else
	if (_detail == "thursday") {
		return ViewType::THURSDAY;
	} else
	if (_detail == "friday") {
		return ViewType::FRIDAY;
	} else 
	if (_detail == "saturday") {
		return ViewType::SATURDAY;
	} else
	if(_detail == "all"){
		return ViewType::ALL;
	}else
    if (_detail == "today") {
		return ViewType::TODAY;
	} else 
	if (_detail == "tomorrow") {
		return ViewType::TOMORROW;
	}else 
	if (_detail == "weekly"){
		return ViewType::WEEKLY;
	} 
	else {
		return ViewType::INVALID;
	}
}

std::string ViewType::filterOutCmd(std::string input) {
	size_t firstWordLength = getFirstWord(input).length();

	if (input.length() > firstWordLength) {
		return input.substr(firstWordLength + 1);
	}

	// only one word in input string.
	return "";
}

std::string ViewType::getFirstWord(std::string input) {
	std::istringstream iss(input);
	std::string firstWord;
	iss >> firstWord;
	return firstWord;
}