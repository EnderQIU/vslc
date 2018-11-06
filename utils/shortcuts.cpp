//
// Created by enderqiu on 2018/11/2.
//

#include "shortcuts.h"


const char *ScanException::what() const noexcept {
    return "A Scan Error Occurred.";
}


const char *ParseException::what() const noexcept {
    return "A Parsing Error Occurred.";
}


const char *CodeGenException::what() const noexcept {
    return "A Code Generation Error Occurred.";
}


/*
 * exc < 0: throw exception
 * exc >= 0: exit with code
 */
void abort(int exc){
    switch (exc){
        case FATALEXCEPTION:
            exit(FATALEXCEPTION);
        case SCANEXCEPTION:
            throw ScanException();
        case PARSEEXCEPTION:
            throw ParseException();
        case CODEGENXCEPTION:
            throw CodeGenException();
        default:
            exit(-1);
    }
}
