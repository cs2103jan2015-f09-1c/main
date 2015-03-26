#include "MappingNumber.h"

MappingNumber* MappingNumber::_instance = 0;

MappingNumber* MappingNumber::getInstance() {
    if (_instance == 0) {
        _instance = new MappingNumber;
    }
    return _instance;
}

void MappingNumber::resetInstance() {
    delete _instance;
    _instance = NULL;
}
void MappingNumber:: addNode(NODE node){
	_displayMapping.push_back(node);
}

void MappingNumber:: clearMappingNumber(){
	_displayMapping.clear();
}

unsigned MappingNumber:: getTaskID(unsigned num) const{
	const_node_iterator iter;
	for(iter=_displayMapping.begin();  iter != _displayMapping.end(); ++iter){
		if(num == iter->displayNum){
			return iter->taskID;
		}
	}
	return 0;
}


MappingNumber::MappingNumber(void){
}

MappingNumber::~MappingNumber(void){
}

