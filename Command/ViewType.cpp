#include "ViewType.h"

ViewType::ViewType(void) {
}

ViewType::~ViewType(void) {
}

ViewType::View ViewType::determineViewType(std::string _detail){
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