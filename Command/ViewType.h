#pragma once
#include <string>

class ViewType {
public:
    enum View{
	    SUNDAY, MONDAY, TUESDAY, WEDNESDAY,
		THURSDAY, FRIDAY, SATURDAY, ALL, TODAY, TOMORROW,
		WEEKLY, INVALID
    };

    ViewType(void);
    ~ViewType(void);

    static View determineViewType(std::string _detail);

};
