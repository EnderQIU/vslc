//
// Created by enderqiu on 2018/9/19.
//

#include "input_buffer.h"

InputBuffer::InputBuffer(vector<Symbol> symbols) {
    if (symbols.empty()){
        cerr<<"ERROR: Parser Error: No tokens found"<<endl;
        abort(PARSEEXCEPTION);
        return;
    }
    this->symbols = symbols;
    this->index = 0;
    this->len = symbols.size();
}

Symbol InputBuffer::present() {
    return symbols.at(index);
}

void InputBuffer::next() {
    index++;
    if (index > len){
        cerr<<"FATAL ERROR: Parser Error: INPUT overflow"<<endl;
        abort(FATALEXCEPTION);
    }
}

bool InputBuffer::is$() {
    return index == len;
}

void InputBuffer::reset() {
    index = 0;
}


