//@Ratnawati Kwanditanto A0113736J
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
	static std::string filterOutCmd(std::string input);

private:
	 static std::string getFirstWord(std::string input);

};
