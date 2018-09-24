#include "ast.h"

void AST::addChild(AST* child) {
    this->children.push_back(child);
    child->setParent(this);
}

AST* AST::getLowerLeftNTNode() {
    if (this->symbol.isTerminal()){
        return this;
    }else if (this->children.size()!=0){
        for(AST* child : this->children){
            AST* currentChild = child->getLowerLeftNTNode();
            if (!currentChild->symbol.isTerminal()){
                return currentChild;
            }
        }
        //if every child of this ast is terminal return a fake terminal tell the parent not me
        return new AST(Symbol(SymbolType::IDENTIFIER));
    }
    return this;
}

AST* AST::getLowerLeftTNode() {
    if (this->symbol.isTerminal()&&this->symbol.type!= SymbolType::EPSILON && this->symbol.value==""){
        return this;
    }
    else if (this->children.size() != 0) {
        for (AST* child : children) {
            AST* currentChild = child->getLowerLeftTNode();
            if (currentChild->symbol.isTerminal() && currentChild->symbol.type != SymbolType::EPSILON && currentChild->symbol.value == "") {
                return currentChild;
            }
        }
    }
    //return a fake non-terminal tell the parent not me
    return new AST(Symbol(SymbolType::A));
    

}

AST::AST(Symbol symbol) {
    this->symbol = symbol;
}

void AST::setParent(AST* parent) {
    this->parent = parent;
}

void AST::setSymbol(Symbol symbol) {
    this->symbol = symbol;
}

AST* AST::copy() {
    AST* newTree = new AST(this->symbol);
    for (int i = 0; i < this->children.size(); i++){
        newTree->addChild(this->children.at(i)->copy(this));
    }
    return newTree;

}
AST* AST::copy(AST* parent) {
    AST* newTree = new AST(this->symbol);
    newTree->setParent(parent->getParent());
    for (int i = 0; i < this->children.size(); i++) {
        newTree->addChild(this->children.at(i)->copy(this));
    }
    return newTree;
}