#pragma once
#include "commandinterface.h"
class ViewCmd : public CommandInterface {
public:
    ViewCmd(void);
	~ViewCmd(void);
	void prepareDetail (std::string detail);
    UIObject execute();

private:
	std::string _detail;
};