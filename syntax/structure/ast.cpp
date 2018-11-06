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

template<typename ReturnType, typename ... ArgumentType>  // Refer to https://msdn.microsoft.com/zh-cn/library/dn439779.aspx
ReturnType AST::gen(ArgumentType&... args) {              // for template usage.
    switch (symbol.type){
        // TODO implement all gen()
        // Inherited from token
        case SymbolType::IDENTIFIER:
            return "b";
        case SymbolType::FUNC:
            return "a";
        case SymbolType::PRINT:
            return "e";
        case SymbolType::RETURN:
            return "g";
        case SymbolType::CONTINUE:
            return "h";
        case SymbolType::IF:
            return "i";
        case SymbolType::THEN:
            return "j";
        case SymbolType::ELSE:
            return "l";
        case SymbolType::FI:
            return "k";
        case SymbolType::WHILE:
            return "m";
        case SymbolType::DO:
            return "n";
        case SymbolType::DONE:
            return "o";
        case SymbolType::VAR:
            return "p";
        case SymbolType::ASSIGN:
            return "c";
        case SymbolType::PLUS:
            return "+";
        case SymbolType::MINUS:
            return "-";
        case SymbolType::MULTIPLY:
            return "*";
        case SymbolType::DIVIDE:
            return "/";
        case SymbolType::L_CURLY_BRACE:
            return "{";
        case SymbolType::R_CURLY_BRACE:
            return "}";
        case SymbolType::L_BRACKET:
            return "(";
        case SymbolType::R_BRACKET:
            return ")";
        case SymbolType::COMMA:
            return ",";
        case SymbolType::INTEGER:
            return "d";
        case SymbolType::TEXT:
            return "f";
        // non-terminators
        case SymbolType::S:
            return "S";
        case SymbolType::A:
            return "A";
        case SymbolType::B:
            return "B";
        case SymbolType::C:
            return "C";
        case SymbolType::D:
            return "D";
        case SymbolType::E:
            return "E";
        case SymbolType::F:
            return "F";
        case SymbolType::G:
            return "G";
        case SymbolType::H:
            return "H";
        case SymbolType::I:
            return "I";
        case SymbolType::J:
            return "J";
        case SymbolType::K:
            return "K";
        case SymbolType::L:
            return "L";
        case SymbolType::M:
            return "M";
        case SymbolType::N:
            return "N";
        case SymbolType::O:
            return "O";
        case SymbolType::P:
            return "P";
        case SymbolType::Q:
            return "Q";
        case SymbolType::R:
            return "R";
        case SymbolType::T:
            return "T";
        case SymbolType::U:
            return "U";
        case SymbolType::V:
            return "V";
        case SymbolType::W:
            return "W";
        // non-terminators with '
        case SymbolType::A_:
            return "A'";
        case SymbolType::E_:
            return "E'";
        case SymbolType::M_:
            return "M'";
        case SymbolType::V_:
            return "V'";
        case SymbolType::W_:
            return "W'";
        case SymbolType::P_:
            return "P'";
        case SymbolType::R_:
            return "R'";
        case SymbolType::T_:
            return "T'";
        case SymbolType::O_:
            return "O'";
        case SymbolType::J_:
            return "J'";
            // Special Symbols
        case SymbolType::EPSILON:
            return "ε";
        case SymbolType::HASHTAG:
            return "#";
        case SymbolType::DOLLAR:
            return "$";
        default:
            cerr << "Code Generation Function for Symbol Type "<< symbol.getDisplay() << " Not Defined." << endl;
            abort(FATALEXCEPTION);
    }
}
