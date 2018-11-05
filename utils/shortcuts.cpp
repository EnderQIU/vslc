//
// Created by enderqiu on 2018/11/2.
//

#include "shortcuts.h"


const char *ParseException::what() const noexcept {
    return "A Parsing Error Occurred.";
}


void abort(int exitNumber, bool forceExit){
    if (forceExit){
        exit(exitNumber);
    }
    if (shellMode){
        return;
    }
    else{
        throw ParseException();
    }
}
