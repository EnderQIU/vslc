//
// Created by enderqiu on 2018/9/17.
//

#ifndef VSLC_AST_H
#define VSLC_AST_H

#include <vector>

#include "symbol.h"

using namespace std;

class AST{
private:
    Symbol symbol = Symbol(SymbolType::EPSILON);
    AST* parent = nullptr;
    vector<AST*> children;
public:
    AST(Symbol symbol);
    bool isLeaf() { return children.empty(); }
    bool isRoot() { return parent == nullptr; }
    AST* getParent() { return parent; }
    AST* getLowerLeftNode();    // find the position of the node which is in the top of parsing stack
    void addChild(AST* child);
    AST() {};
    void setParent(AST* parent);
};

#endif //VSLC_AST_H
