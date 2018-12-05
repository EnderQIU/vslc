//
// Created by enderqiu on 2018/9/19.
//

#include "symbol.h"

Symbol::Symbol(Token token) {
    switch (token.type){
        case TokenType::IDENTIFIER:
            this->type = SymbolType::IDENTIFIER;
            break;
        case TokenType::FUNC:
            this->type = SymbolType::FUNC;
            break;
        case TokenType::PRINT:
            this->type = SymbolType::PRINT;
            break;
        case TokenType::RETURN:
            this->type = SymbolType::RETURN;
            break;
        case TokenType::CONTINUE:
            this->type = SymbolType::CONTINUE;
            break;
        case TokenType::IF:
            this->type = SymbolType::IF;
            break;
        case TokenType::THEN:
            this->type = SymbolType::THEN;
            break;
        case TokenType::ELSE:
            this->type = SymbolType::ELSE;
            break;
        case TokenType::FI:
            this->type = SymbolType::FI;
            break;
        case TokenType::WHILE:
            this->type = SymbolType::WHILE;
            break;
        case TokenType::DO:
            this->type = SymbolType::DO;
            break;
        case TokenType::DONE:
            this->type = SymbolType::DONE;
            break;
        case TokenType::VAR:
            this->type = SymbolType::VAR;
            break;
        case TokenType::ASSIGN:
            this->type = SymbolType::ASSIGN;
            break;
        case TokenType::PLUS:
            this->type = SymbolType::PLUS;
            break;
        case TokenType::MINUS:
            this->type = SymbolType::MINUS;
            break;
        case TokenType::MULTIPLY:
            this->type = SymbolType::MULTIPLY;
            break;
        case TokenType::DIVIDE:
            this->type = SymbolType::DIVIDE;
            break;
        case TokenType::L_CURLY_BRACE:
            this->type = SymbolType::L_CURLY_BRACE;
            break;
        case TokenType::R_CURLY_BRACE:
            this->type = SymbolType::R_CURLY_BRACE;
            break;
        case TokenType::L_BRACKET:
            this->type = SymbolType::L_BRACKET;
            break;
        case TokenType::R_BRACKET:
            this->type = SymbolType::R_BRACKET;
            break;
        case TokenType::COMMA:
            this->type = SymbolType::COMMA;
            break;
        case TokenType::INTEGER:
            this->type = SymbolType::INTEGER;
            break;
        case TokenType::TEXT:
            this->type = SymbolType::TEXT;
            break;
        default:
            cout<<"FATAL ERROR: Error: No such token"<<endl;
            abort(FATALEXCEPTION);
    }
    this->value = token.value;
    this->line = token.line;
    this->column = token.column;
    this->isToken = true;
}

Symbol::Symbol(SymbolType type) {
    this->type = type;
}

string Symbol::getDisplay() {
    switch (this->type){
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
            cout<<"FATAL ERROR: Error: Can't display such symbol."<<endl;
            abort(FATALEXCEPTION);
    }
}

bool Symbol::isTerminal() {
    switch (this->type){
        // non-terminators
        case SymbolType::S:
            return false;
        case SymbolType::A:
            return false;
        case SymbolType::B:
            return false;
        case SymbolType::C:
            return false;
        case SymbolType::D:
            return false;
        case SymbolType::E:
            return false;
        case SymbolType::F:
            return false;
        case SymbolType::G:
            return false;
        case SymbolType::H:
            return false;
        case SymbolType::I:
            return false;
        case SymbolType::J:
            return false;
        case SymbolType::K:
            return false;
        case SymbolType::L:
            return false;
        case SymbolType::M:
            return false;
        case SymbolType::N:
            return false;
        case SymbolType::O:
            return false;
        case SymbolType::P:
            return false;
        case SymbolType::Q:
            return false;
        case SymbolType::R:
            return false;
        case SymbolType::T:
            return false;
        case SymbolType::U:
            return false;
        case SymbolType::V:
            return false;
        case SymbolType::W:
            return false;
        // non-terminators with '
        case SymbolType::A_:
            return false;
        case SymbolType::E_:
            return false;
        case SymbolType::M_:
            return false;
        case SymbolType::V_:
            return false;
        case SymbolType::W_:
            return false;
        case SymbolType::P_:
            return false;
        case SymbolType::R_:
            return false;
        case SymbolType::T_:
            return false;
        case SymbolType::O_:
            return false;
        case SymbolType::J_:
            return false;
        default:
            // else are terminals
            return true;
    }
}

string Symbol::getTypeName() {
    switch (this->type) {
        case SymbolType::IDENTIFIER:
            return "IDENTIFIER";
        case SymbolType::FUNC:
            return "FUNC";
        case SymbolType::PRINT:
            return "PRINT";
        case SymbolType::RETURN:
            return "RETURN";
        case SymbolType::CONTINUE:
            return "CONTINUE";
        case SymbolType::IF:
            return "IF";
        case SymbolType::THEN:
            return "THEN";
        case SymbolType::ELSE:
            return "ELSE";
        case SymbolType::FI:
            return "FI";
        case SymbolType::WHILE:
            return "WHILE";
        case SymbolType::DO:
            return "DO";
        case SymbolType::DONE:
            return "DONE";
        case SymbolType::VAR:
            return "VAR";
        case SymbolType::ASSIGN:
            return "ASSIGN";
        case SymbolType::PLUS:
            return "PLUS";
        case SymbolType::MINUS:
            return "MINUS";
        case SymbolType::MULTIPLY:
            return "MULTIPLY";
        case SymbolType::DIVIDE:
            return "DIVIDE";
        case SymbolType::L_CURLY_BRACE:
            return "L_CURLY_BRACE";
        case SymbolType::R_CURLY_BRACE:
            return "R_CURLY_BRACE";
        case SymbolType::L_BRACKET:
            return "L_BRACKET";
        case SymbolType::R_BRACKET:
            return "R_BRACKET";
        case SymbolType::COMMA:
            return "COMMA";
        case SymbolType::INTEGER:
            return "INTEGER";
        case SymbolType::TEXT:
            return "TEXT";
        default:
            return getDisplay();
    }
}
