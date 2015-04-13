//@Ratnawati Kwanditanto A0113736J
#pragma once
#include <list>

class MappingNumber{
public:
	MappingNumber(void);
	~MappingNumber(void);

	struct NODE {
		unsigned taskID;
		unsigned displayNum;
	};
	typedef std::list<NODE> node;
	typedef std::list<NODE>::iterator node_iterator;
    typedef std::list<NODE>::const_iterator const_node_iterator;

	static MappingNumber* getInstance();
    static void resetInstance(); 
	void addNode(NODE node);
	int countNode();
	void clearMappingNumber(); // everytime a fresh set of tasks is displayed on textUI, and we want to add a fresh set of nodes, we should clear everything in the vector. If not will have duplicates
	unsigned getTaskID(unsigned num) const;// pass in a number on screen,
	//should return corresponding taskID

private:
	node _displayMapping;
	static MappingNumber* _instance;
	
};