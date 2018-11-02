//
// Created by enderqiu on 2018/11/2.
//

#include "shortcuts.h"

void abort(int exitNumber, bool forceExit){
    if (forceExit){
        exit(exitNumber);
    }
    if (shellMode){
        return;
    }
    else{
        exit(exitNumber);
    }
}

