//
// Created by enderqiu on 2018/9/15.
//

#ifndef VSLC_TOKEN_H
#define VSLC_TOKEN_H

#include <string>
#include <iostream>
#include <utility>


using namespace std;

enum class TokenType{  // Due to enum can't be duplicate, use enum class instead enum for SymbolType
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

    // Delimiter
    DELIMITER,  // Example: {whitespace}, {tab}, \n, \r

    // Comment
    COMMENT,
};


class Token {
public:
    TokenType type = TokenType::IDENTIFIER;
    bool isGrammatical = true;  // Have grammatical meaning or not, decide whether to pass it to parser.
    string value;
    unsigned long line = 1;
    unsigned long column = 1;

    Token(TokenType type, bool isGrammatical, string value);
    Token() = default;
    Token(const Token& token);  // deep copy contructor
    string getDisplay();
};

#endif //VSLC_TOKEN_H
