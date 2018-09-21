//
// Created by enderqiu on 2018/9/19.
//

#ifndef VSLC_PRODUCTION_H
#define VSLC_PRODUCTION_H

#include <vector>

#include "symbol.h"

using namespace std;

class Production {
public:
    Symbol left = Symbol(SymbolType::EPSILON);  // left part of a production -- a non-terminator
    vector<Symbol> right;  // right part of a production -- a bunch of terminators
    Production(Symbol left, vector<Symbol> right);
    Production() = default;

    void display();
};

#endif //VSLC_PRODUCTION_H
