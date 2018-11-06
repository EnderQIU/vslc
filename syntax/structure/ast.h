//
// Created by enderqiu on 2018/9/17.
//

#ifndef VSLC_AST_H
#define VSLC_AST_H

#include <vector>

#include "symbol.h"
#include "../../utils/engine.h"

using namespace std;

extern llvm::LLVMContext context;
extern llvm::IRBuilder<> builder;
extern llvm::Module * module;
extern std::map<std::string, llvm::Value *> namedValues;


class AST{
private:
    Symbol symbol = Symbol(SymbolType::EPSILON);
    AST* parent = nullptr;
    AST* copy(AST*);
    void print(vector<AST*> nodes, string prefix);
public:
    vector<AST*> children;
    AST(Symbol symbol);
    bool isLeaf() { return children.empty(); }
    bool isRoot() { return parent == nullptr; }
    AST* getParent() { return parent; }
    Symbol getSymbol() { return symbol; }
    AST* getLowerLeftNTNode();    // find the non-terminal node which is in the top of parsing stack
    AST* getLowerLeftTNode();   // find the terminal node which is in the top of inputbuffer
    void addChild(AST* child);
    void setSymbol(Symbol symbol);
    AST() {};
    void setParent(AST* parent);
    AST* copy();
    void print();
};

#endif //VSLC_AST_H
