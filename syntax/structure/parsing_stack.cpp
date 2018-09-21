//
// Created by enderqiu on 2018/9/19.
//

#include "parsing_stack.h"


Symbol ParsingStack::top() {
    if (symbols.empty()) {
        cerr<<"FATAL ERROR: Parser Error: Call top() when parsing stack is empty"<<endl;
        exit(-1);
    }
    return symbols.top();
}


void ParsingStack::pop() {
    return symbols.pop();
}

void ParsingStack::push(Symbol symbol) {
    symbols.push(symbol);
}

bool ParsingStack::empty() {
    return symbols.empty();
}
