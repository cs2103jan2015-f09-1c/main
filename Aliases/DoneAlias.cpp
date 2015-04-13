//@author A0113736J
#include "DoneAlias.h"
#include <algorithm> //std::transform
#include <sstream>

void DoneAlias::removeSpaces(std::string &input) {
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
}

DoneAlias::DoneAlias(void) {
}


DoneAlias::~DoneAlias(void) {
}

bool DoneAlias::isInteger(std::string detail) {
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

bool DoneAlias::isHelp(std::string detail) {
	removeSpaces(detail);
	return detail == "";
}