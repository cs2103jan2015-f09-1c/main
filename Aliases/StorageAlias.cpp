#include "StorageAlias.h"
#include <algorithm> //std::transform

void StorageAlias::removeSpaces(std::string &input) {
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
}

StorageAlias::StorageAlias(void) {
}


StorageAlias::~StorageAlias(void) {
}

bool StorageAlias::isGetLocation(std::string alias) {
	std::transform(alias.begin(), alias.end(), alias.begin(), ::tolower);
	return alias == "location" || alias == "loc";
}

bool StorageAlias::isHelp(std::string alias) {
	removeSpaces(alias);
	return alias == "";
}