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
    DIVIDE = 17,

    SEPARATOR = -3,
    // Separator: {, }, (, ), ,
    L_CURLY_BRACE = 18,
    R_CURLY_BRACE = 19,
    L_BRACKET = 20,
    R_BRACKET = 21,
    COMMA = 22,

    // Primitive
    INTEGER = 23,
    TEXT = 24,

    // Delimiter
    DELIMITER = 25,  // Example: {whitespace}, {tab}, \n, \r

    // Comment
    COMMENT = 26,
};

// NOLINTNEXTLINE
const static string TokenTypeName[27] = {
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
        "DIVIDE",
        "L_CURLY_BRACE",
        "R_CURLY_BRACE",
        "L_BRACKET",
        "R_BRACKET",
        "COMMA",
        "INTEGER",
        "TEXT",
        "DELIMITER",
        "COMMENT",
};

// Abstract base class
class Token {
public:
    TokenType type = IDENTIFIER;
    bool isGrammatical = true;  // Have grammatical meaning or not, decide whether to pass it to parser.
    string value;
    unsigned long line = 1;
    unsigned long column = 1;

    Token(TokenType type, bool isGrammatical, string value);
    Token() = default;
};

#endif //VSLC_TOKEN_H
