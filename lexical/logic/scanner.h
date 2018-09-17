//
// Created by enderqiu on 2018/9/15.
//

#ifndef VSLC_SCANNER_H
#define VSLC_SCANNER_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <iomanip>

#include "../structure/token.h"
#include "../../utils/source_code_reader.h"

using namespace std;

class Scanner {
private:
    vector<Token> token_list;  // result of lexical analysis
    char state;  // state of DFA
    string char_stack;
    char present_char;
    SourceCodeReader* source_code;

    bool isDelimiter(char c);
    bool isSeparator(char c);
    bool isColon(char c);
    bool isEqualSign(char c);
    bool isOperator(char c);
    bool isSlash(char c);
    bool isLineBreak(char c);
    bool isDigit(char c);
    bool isQuotationMark(char c);
    void _scan();
    void _displayResult();
    void initState();
    void switchState(char targetState);
    void addToken(TokenType type, bool isGrammatical);
    void _raiseScanError(string reason);
    void _raiseFatalError(string reason);
public:
    explicit Scanner(SourceCodeReader* reader);
    vector<Token> scan(bool verboseMode);
};


#endif //VSLC_SCANNER_H
