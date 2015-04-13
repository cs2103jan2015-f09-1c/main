//@Pham Thi Hong A0113955A
#include "DeleteAlias.h"
#include <algorithm> //std::transform
#include <sstream>

void DeleteAlias::removeSpaces(std::string &input) {
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
}

DeleteAlias::DeleteAlias(void) {
}


DeleteAlias::~DeleteAlias(void) {
}

bool DeleteAlias::isInteger(std::string detail) {
	int integer;
	std::stringstream convert (detail);
	convert >> integer;

	if (convert.fail()){
		integer = 0;
	}
	else{
		integer = 1 ;
	}
	return integer;
}

bool DeleteAlias::isHelp(std::string detail) {
	removeSpaces(detail);
	return detail == "";
}