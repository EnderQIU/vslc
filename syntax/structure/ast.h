//
// Created by enderqiu on 2018/9/17.
//

#ifndef VSLC_AST_H
#define VSLC_AST_H

#include <vector>

#include "symbol.h"
#include "../../utils/engine.h"


using namespace std;

class AST{
private:
    Symbol symbol = Symbol(SymbolType::EPSILON);
    AST* parent = nullptr;
    AST* copy(AST*);
    void print(vector<AST*> nodes, string prefix);
    // LLVM IR code generation for specific node ... about 56 functions

public:
    vector<AST*> children;

    explicit AST(Symbol symbol);
    bool isLeaf() { return children.empty(); }
    bool isRoot() { return parent == nullptr; }
    AST* getParent() { return parent; }
    Symbol getSymbol() { return symbol; }
    AST* getLowerLeftNTNode();    // find the non-terminal node which is in the top of parsing stack
    AST* getLowerLeftTNode();   // find the terminal node which is in the top of inputbuffer
    void addChild(AST* child);
    void setSymbol(Symbol symbol);
    AST() = default;;
    void setParent(AST* parent);
    AST* copy();
    void print();
    template<typename T> T gen(T returnType);  // LLVM IR code generation. Decide which gen() function to use.
};

#endif //VSLC_AST_H
