//
// Created by enderqiu on 2018/9/15.
//

#include "token.h"

Token::Token(TokenType type, bool isGrammatical, string value) {
    this->type = type;
    this->isGrammatical = isGrammatical;
    this->value = std::move(value);
}

string Token::getDisplay() {
    switch (this->type){
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::FUNC:
            return "FUNC";
        case TokenType::PRINT:
            return "PRINT";
        case TokenType::RETURN:
            return  "RETURN";
        case TokenType::CONTINUE:
            return "CONTINUE";
        case TokenType::IF:
            return "IF";
        case TokenType::THEN:
            return "THEN";
        case TokenType::ELSE:
            return "ELSE";
        case TokenType::FI:
            return "FI";
        case TokenType::WHILE:
            return "WHILE";
        case TokenType::DO:
            return "DO";
        case TokenType::DONE:
            return "DONE";
        case TokenType::VAR:
            return "VAR";
        case TokenType::ASSIGN:
            return "ASSIGN";
        case TokenType::PLUS:
            return "PLUS";
        case TokenType::MINUS:
            return "MINUS";
        case TokenType::MULTIPLY:
            return "MULTIPLY";
        case TokenType::DIVIDE:
            return "DIVIDE";
        case TokenType::L_CURLY_BRACE:
            return "L_CURLY_BRACE";
        case TokenType::R_CURLY_BRACE:
            return "R_CURLY_BRACE";
        case TokenType::L_BRACKET:
            return "L_BRACKET";
        case TokenType::R_BRACKET:
            return "R_BRACKET";
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::INTEGER:
            return "INTEGER";
        case TokenType::TEXT:
            return "TEXT";
        case TokenType::DELIMITER:
            return "DELIMITER";
        case TokenType::COMMENT:
            return "COMMENT";
        default:
            cout<<"FATAL ERROR: Error: No such token"<<endl;
            exit(-1);
    }
}

Token::Token(const Token &token) {
    this->type = token.type;
    this->isGrammatical = token.isGrammatical;
    this->line = token.line;
    this->column = token.column;
    this->value = token.value;
}
