//
// Created by enderqiu on 2018/11/2.
//

#ifndef VSLC_SHORTCUTS_H
#define VSLC_SHORTCUTS_H

#define FATALEXCEPTION  1
#define SCANEXCEPTION   -1
#define PARSEEXCEPTION  -2
#define CODEGENXCEPTION -3

#include <exception>
#include <cstdlib>


class SourceCodeReaderException: public std::exception{};

class CompileException: public std::exception{};


/*
 * Exception during lexical analysis
 */
class ScanException: public CompileException{
public:
    const char* what()const noexcept override;
};


/*
 * Exception during syntax analysis
 */
class ParseException: public CompileException{
public:
    const char* what()const noexcept override;
};


/*
 * Exception during LLVM IR code generation
 */
class CodeGenException: public CompileException{
public:
    const char* what()const noexcept override;
};


/*
 * Abort execution unlike exit()
 */
void abort(int exc);

#endif //VSLC_SHORTCUTS_H
