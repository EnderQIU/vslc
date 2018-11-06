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

string PREFIX_BRANCH = "├─";  // 树枝
string PREFIX_TRUNK = "│ ";   // 树干
string PREFIX_LEAF = "└─";    // 叶子
string PREFIX_EMP = "  ";     // 空

string& replace_all_distinct(string& str, const string& old_value, const string& new_value) {
    for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
        if ((pos = str.find(old_value, pos)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        else
            break;
    }
    return  str;
}

void AST::print(vector<AST*> nodes, string prefix) {
    prefix = replace_all_distinct(prefix, PREFIX_BRANCH, PREFIX_TRUNK);
    prefix = replace_all_distinct(prefix, PREFIX_LEAF, PREFIX_EMP);
    for (int i = 0; i < nodes.size(); i++) {
        if (i == nodes.size() - 1) {
            cout << prefix << PREFIX_LEAF << "  " << nodes[i]->getSymbol().getTypeName() << endl;
            if (!nodes[i]->isLeaf()) {
                this->print(nodes[i]->children, prefix + PREFIX_LEAF);
            }
        }
        else {
            cout << prefix << PREFIX_BRANCH << "  " << nodes[i]->getSymbol().getTypeName() << endl;
            if (!nodes[i]->isLeaf()) {
                this->print(nodes[i]->children, prefix + PREFIX_TRUNK);
            }
        }
    }
}

void AST::print() {
    cout << '\n' << "AST TREE" << endl;
    cout << PREFIX_LEAF << "  " << this->getSymbol().getTypeName() << endl;
    this->print(this->children, PREFIX_LEAF);
}

template<typename T>
T AST::gen(T returnType) {
    switch (symbol.type){
        case SymbolType::S:
            return children[0]->gen<T>();
        default:
            break;
    }
}
