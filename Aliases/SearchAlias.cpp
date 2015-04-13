#include "SearchAlias.h"
#include <algorithm> //std::transform
#include <sstream>

void SearchAlias::removeSpaces(std::string &input) {
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
}

SearchAlias::SearchAlias(void) {
}


SearchAlias::~SearchAlias(void) {
}

bool SearchAlias::isHelp(std::string detail) {
	removeSpaces(detail);
	return detail == "";
}