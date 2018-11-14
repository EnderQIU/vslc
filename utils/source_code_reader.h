//
// Created by enderqiu on 2018/9/16.
//

#ifndef VSLC_SOURCE_CODE_READER_H
#define VSLC_SOURCE_CODE_READER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

extern bool verboseMode, shellMode;

using namespace std;

class SourceCodeReader{
private:
    string filename;
    string content;  // store source code in one line, include the '\n'
    vector<string> line;  // store the source code in a map container for debug
    size_t len = 0;
    unsigned long offset = 0;
public:
    unsigned long line_num = 1;  // line_num start at 1
    unsigned long column = 1;  // column start at 1
    explicit SourceCodeReader(string filename);
    void resetOffset();
    char getNextChar();
    char lookNextChar();  // get next char without move offset
    string getLine(unsigned long line_num);
    bool isEOF();  // offset reaches the End Of File.
    SourceCodeReader();   // Constructor for shell mode
    void addLine(string aline);
};


#endif //VSLC_SOURCE_CODE_READER_H
