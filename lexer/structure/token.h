//
// Created by enderqiu on 2018/9/15.
//

#ifndef VSLC_TOKEN_H
#define VSLC_TOKEN_H

#include <string>

using namespace std;

enum TokenType{
    IDENTIFIER = 0,
    // Identifier
    FUNC = 1,
    PRINT = 2,
    RETURN = 3,
    CONTINUE = 4,
    IF = 5,
    THEN = 6,
    ELSE = 7,
    FI = 8,
    WHILE = 9,
    DO = 10,
    DONE = 11,
    VAR = 12,  // Variable  a special type of identifier

    ASSIGN = 13,  // :=

    OPERATOR = -2,
    // Operator
    PLUS = 14,
    MINUS = 15,
    MULTIPLY = 16,

    SEPARATOR = -3,
    // Separator: {, }, (, ), ,
    L_CURLY_BRACE = 17,
    R_CURLY_BRACE = 18,
    L_BRACKET = 19,
    R_BRACKET = 20,
    COMMA = 21,

    // Delimiter
    DELIMITER = 22,  // Example: {whitespace}, {tab}, \n, \r

    // Primitive
    INTEGER = 23,
    TEXT = 24,

    // Comment
    COMMENT = 25,
};

// NOLINTNEXTLINE
const static string TokenTypeName[26] = {
        "IDENTIFIER",
        "FUNC",
        "PRINT",
        "RETURN",
        "CONTINUE",
        "IF",
        "THEN",
        "ELSE",
        "FI",
        "WHILE",
        "DO",
        "DONE",
        "VAR",
        "ASSIGN",
        "PLUS",
        "MINUS",
        "MULTIPLY",
        "L_CURLY_BRACE",
        "R_CURLY_BRACE",
        "L_BRACKET",
        "R_BRACKET",
        "COMMA",
        "DELIMITER",
        "INTEGER",
        "TEXT",
        "COMMENT",
};

// Abstract base class
class Token {
public:
    TokenType type = IDENTIFIER;
    bool isGrammatical = true;  // Have grammatical meaning || not, decide whether to pass it to parser.
    string value;
    unsigned long line = 1;
    unsigned long column = 1;

    Token(TokenType type, bool isGrammatical, string value);
    Token() = default;
};

#endif //VSLC_TOKEN_H
