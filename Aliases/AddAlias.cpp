#include "AddAlias.h"
#include <algorithm> //std::transform
#include <sstream>

void AddAlias::removeSpaces(std::string &input) {
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
}

AddAlias::AddAlias(void) {
}

AddAlias::~AddAlias(void) {
}

bool AddAlias::isHelp(std::string detail) {
	removeSpaces(detail);
	return detail == "";
}