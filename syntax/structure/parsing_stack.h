//
// Created by enderqiu on 2018/9/19.
//

#ifndef VSLC_PARSING_STACK_H
#define VSLC_PARSING_STACK_H

#include <stack>

#include "symbol.h"
#include "../../utils/shortcuts.h"


extern void abort();

using namespace std;

class ParsingStack {
private:
    stack<Symbol> symbols;
public:
    ParsingStack() = default;
    Symbol top();
    void pop();
    void push(Symbol symbol);
    void clear();
    bool empty();
};


#endif //VSLC_PARSING_STACK_H
