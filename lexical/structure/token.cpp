#include <utility>

#include <utility>

//
// Created by enderqiu on 2018/9/15.
//

#include "token.h"

Token::Token(TokenType type, bool isGrammatical, string value) {
    this->type = type;
    this->isGrammatical = isGrammatical;
    this->value = std::move(value);
}
