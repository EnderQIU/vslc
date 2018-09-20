//
// Created by enderqiu on 2018/9/19.
//

#include "parsing_stack.h"


Symbol ParsingStack::top() {
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
