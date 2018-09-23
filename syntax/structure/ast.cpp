#include "ast.h"

void AST::addChild(AST* child) {
    this->children.push_back(child);
    child->parent = this;
}

AST* AST::getLowerLeftNode() {
    if (this->symbol.isTerminal()){
        return this;
    }else if (children.size()!=0){
        for each(AST* child in children){
            AST* currentChild = child->getLowerLeftNode();
            if (!currentChild->symbol.isTerminal()){
                return currentChild;
            }
        }
        //if every child of this ast is terminal return a fake terminal tell the parent not me
        return new AST(Symbol(SymbolType::IDENTIFIER));
    }
    return this;
}

AST::AST(Symbol symbol) {
    this->symbol = symbol;
}

void AST::setParent(AST* parent) {
    this->parent = parent;
}