#include "Interpreter.h"
#include <iostream>
const size_t Interpreter::NUM_CHARS_STORAGE = 7;

Task Interpreter::parseAddCmd(std::string input) {
    //think of how to break down the string into attributes 
    //which we can store into DS::TASK
    //tip- user needs to put colon ":" before specifying details
    //(refer to dropbox commoncommands.txt)

    Task a;
    return a;
}

Task Interpreter::parseEditCmd(std::string input) {
    Task a;
    return a;
}

std::string Interpreter::parseStoreCmd(std::string input) {    
    std::string cmdDetails;
    if (input == "storage") { 
        return "location";
    }
    cmdDetails = input.substr(NUM_CHARS_STORAGE + 1); //+1 due to space
    //todo: check whether substr is either "location" or
    // a valid filepath

    return cmdDetails;
}

Interpreter::Interpreter(void) {
}


Interpreter::~Interpreter(void) {
}
