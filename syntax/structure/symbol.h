//
// Created by enderqiu on 2018/9/19.
//

#ifndef VSLC_SYMBOL_H
#define VSLC_SYMBOL_H


#include "../../lexical/structure/token.h"

enum class SymbolType {
    // Inherited from TokenType, removed some non-grammatical token types

    IDENTIFIER,
    // Identifier: We regard Keyword as a subclass of identifier
    FUNC,
    PRINT,
    RETURN,
    CONTINUE,
    IF,
    THEN,
    ELSE,
    FI,
    WHILE,
    DO,
    DONE,
    VAR,  // Variable  a special type of identifier

    ASSIGN,  // :=

    OPERATOR,
    // Operator
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,

    SEPARATOR,
    // Separator: {, }, (, ), ,
    L_CURLY_BRACE,
    R_CURLY_BRACE,
    L_BRACKET,
    R_BRACKET,
    COMMA,

    // Primitive
    INTEGER,
    TEXT,


    // Non-terminators: We use underline instead of single quote for c++ grammar

    S,
    A,
    B,
    A_,
    C,
    E,
    E_,
    D,
    F,
    M,
    M_,
    V,
    V_,
    W,
    W_,
    N,
    O,
    P,
    P_,
    Q,
    R,
    R_,
    T,
    T_,
    O_,
    U,
    G,
    H,
    I,
    J,
    K,
    L,
    J_,

    // Special Symbol

    EPSILON,  // a.k.a ε
    HASHTAG,  // a.k.a #
    DOLLAR,   // a.k.a $ We use it as the end of input buffer and parsing stack
};

class Symbol {
public:
    SymbolType type;
    string value = "";
    bool isToken = false;
    unsigned long line;
    unsigned long column;

    explicit Symbol(Token *token);  // Use Token to initialize a symbol
    explicit Symbol(SymbolType type);  // Initialize non-terminators and some special symbol, the line and column can be set later.
    string getDisplay();
    bool isTerminal();
};


#endif //VSLC_SYMBOL_H
