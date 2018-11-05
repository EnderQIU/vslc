//
// Created by enderqiu on 2018/11/2.
//

#ifndef VSLC_SHORTCUTS_H
#define VSLC_SHORTCUTS_H

#include <exception>
#include <cstdlib>


class CompileException: public std::exception{};


class ParseException: public CompileException{
public:
    const char* what()const noexcept override;
};

/*
 * Abort execution unlike exit()
 */
void abort(int exitNumber, bool forceExit=false);

#endif //VSLC_SHORTCUTS_H
