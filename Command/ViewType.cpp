#include "ViewType.h"
#include <sstream>
#include <algorithm>

ViewType::ViewType(void) {
}

ViewType::~ViewType(void) {
}

ViewType::View ViewType::determineViewType(std::string _detail){
	
	std::transform(_detail.begin(), _detail.end(), _detail.begin(), ::tolower);
	_detail.erase(std::remove(_detail.begin(), _detail.end(), ' '), _detail.end());
    
	if (_detail == "sunday" || _detail == "sun") {
		return ViewType::SUNDAY;
	} else
	if (_detail == "monday" || _detail == "mon") {
		return ViewType::MONDAY;
	} else
	if (_detail == "tuesday" || _detail == "tue") {
		return ViewType::TUESDAY;
	} else
	if (_detail == "wednesday" || _detail == "wed") {
		return ViewType::WEDNESDAY;
	} else
	if (_detail == "thursday" || _detail == "thu") {
		return ViewType::THURSDAY;
	} else
	if (_detail == "friday" || _detail == "fri") {
		return ViewType::FRIDAY;
	} else 
	if (_detail == "saturday" || _detail == "sat") {
		return ViewType::SATURDAY;
	} else
	if(_detail == "all" || _detail == "a"){
		return ViewType::ALL;
	}else
    if (_detail == "today" || _detail == "t") {
		return ViewType::TODAY;
	} else 
	if (_detail == "tomorrow" || _detail == "tom" || _detail == "tmr") {
		return ViewType::TOMORROW;
	}else 
	if (_detail == "weekly" || _detail == "week"){
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