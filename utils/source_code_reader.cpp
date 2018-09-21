//
// Created by enderqiu on 2018/9/16.
//

#include "source_code_reader.h"

SourceCodeReader::SourceCodeReader(string filename) {
    ifstream fin(filename.c_str());
    if(!fin){
        cerr << "ERROR: Source Code Reader: Cannot open " << filename << endl;
        exit(-1);
    }
    this->filename = filename;
    string s;
    len = 0;
    content = "";
    while (getline(fin, s)){
        line.push_back(s + '\n');  // getline() will cut off the '\n'
        content += s + '\n';
    }
    if (content.empty()){
        cerr<<"ERROR: Source Code Reader: Empty source code file."<<endl;
        exit(-1);
    }
    len = content.size();
}

void SourceCodeReader::resetOffset() {
    offset = 0;
    line_num = 1;
    column = 1;
}

char SourceCodeReader::getNextChar() {
    offset++;
    if (offset > len){
        cerr<<"FATAL ERROR: Source Code Reader: Offset overflow."<<endl;
        exit(-1);
    }
    if (line[line_num - 1][column - 1] == '\n'){
        line_num ++;
        column = 1;
    }else{
        column++;
    }
    return content.at(offset - 1);
}

bool SourceCodeReader::isEOF() {
    return offset >= len;
}

string SourceCodeReader::getLine(unsigned long line_num) {
    return this->line.at(line_num - 1).erase(this->line.at(line_num - 1).size()-1, 1);
}

char SourceCodeReader::lookNextChar() {
    return content.at(offset);
}
