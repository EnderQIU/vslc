#include <utility>

//
// Created by enderqiu on 2018/9/15.
//

#include "scanner.h"

bool Scanner::isDelimiter(char c) {
    // 32 = {space}; 9 = {tab}; 10 = \n; 13 = \r
    return c == 32 || c == 9 || c == 10 || c == 13;
}

bool Scanner::isSeparator(char c) {
    // 40 = (; 41 = ); 44 = ,; 123 = {; 125 = }
    return c == 40 || c == 41 || c == 44 || c == 123 || c == 125;
}

bool Scanner::isColon(char c) {
    // 58 = :
    return c == 58;
}

bool Scanner::isEqualSign(char c) {
    // 61 = =
    return c == 61;
}

bool Scanner::isOperator(char c) {
    // 42 = *; 43 = +; 45 = -
    return c == 42 || c == 43 || c == 45;
}

bool Scanner::isSlash(char c) {
    // 47 = /
    return c == 47;
}

bool Scanner::isLineBreak(char c) {
    return c == 10 || c == 13;
}

bool Scanner::isDigit(char c) {
    return c > 47 && c < 58;
}

bool Scanner::isQuotationMark(char c) {
    // 34 = "
    return c == 34;
}

void Scanner::initState() {
    state = 's';
    char_stack = "";
}

void Scanner::switchState(char targetState) {
    if (targetState == 's'){
        cout << "FATAL ERROR: Lexer error: State 's' is not switchable, please use initState() instead." << endl;
        exit(-1);
    }
    this->state = targetState;
}

void Scanner::addToken(TokenType type, bool isGrammatical) {
    string value = char_stack;
    Token token;
    if (type == IDENTIFIER){
        if (value == "FUNC") token = Token(FUNC, true, value);
        else if (value == "PRINT") token = Token(PRINT, true, value);
        else if (value == "RETURN") token = Token(RETURN, true, value);
        else if (value == "CONTINUE") token = Token(CONTINUE, true, value);
        else if (value == "IF") token = Token(IF, true, value);
        else if (value == "THEN") token = Token(THEN, true, value);
        else if (value == "ELSE") token = Token(ELSE, true, value);
        else if (value == "FI") token = Token(FI, true, value);
        else if (value == "WHILE") token = Token(WHILE, true, value);
        else if (value == "DO") token = Token(DO, true, value);
        else if (value == "DONE") token = Token(DONE, true, value);
        else if (value == "VAR") token = Token(VAR, true, value);
        else token = Token(IDENTIFIER, true, value);

    }
    else if (type == OPERATOR) {
        if (value == "+") token = Token(PLUS, true, value);
        else if (value == "-") token = Token(MINUS, true, value);
        else if (value == "*") token = Token(MULTIPLY, true, value);
        else if (value == "/") token = Token(DIVIDE, true, value);
        else _raiseScanError("Invalid operator type \"" + value + "\"");

    }
    else if (type == SEPARATOR) {
        if (value == "{") token = Token(L_CURLY_BRACE, true, value);
        else if (value == "}") token = Token(R_CURLY_BRACE, true, value);
        else if (value == "(") token = Token(L_BRACKET, true, value);
        else if (value == ")") token = Token(R_BRACKET, true, value);
        else if (value == ",") token = Token(COMMA, true, value);
        else _raiseScanError("Invalid separator type \"" + value + "\"");
    }
    else if (type == TEXT) {
        token = Token(TEXT, false, value);
    }
    else{
        token = Token(type, isGrammatical, value);
    }
    if (value == "\n") {
        token.line = source_code->line_num - 1;
        token.column = source_code->getLine(token.line).size();
    }else{
        token.line = source_code->line_num;
        token.column = source_code->column - value.size();
    }
    token_list.push_back(token);
    initState();  //  go to start state
}


void Scanner::_scan(){
    initState();

    // there are only switchState() || addToken() before line 'break;'
    while (!source_code->isEOF()){
        switch (state){
            case 's':
                // recognize
                present_char = source_code->getNextChar();
                if (isalpha(present_char)){
                    switchState('a');
                    char_stack += present_char;
                    break;
                }
                if(isDelimiter(present_char)){
                    switchState('c');
                    char_stack += present_char;
                    break;
                }
                if(isSeparator(present_char)){
                    switchState('d');
                    char_stack += present_char;
                    break;
                }
                if(isOperator(present_char)){
                    switchState('e');
                    char_stack += present_char;
                    break;
                }
                if(isSlash(present_char)){
                    switchState('f');
                    char_stack += present_char;
                    break;
                }
                if(isDigit(present_char)){
                    switchState('i');
                    char_stack += present_char;
                    break;
                }
                if(isQuotationMark(present_char)){
                    switchState('k');
                    char_stack += present_char;
                    break;
                }
                if(isColon(present_char)){
                    switchState('m');
                    char_stack += present_char;
                    break;
                }
                _raiseScanError("Unexpected token");  // State not switched means Unexpected token
                break;
            case 'a':
                // outlook -- no stack push op!
                if (isDelimiter(source_code->lookNextChar())
                || isSeparator(source_code->lookNextChar())
                || isOperator(source_code->lookNextChar())
                || isColon(source_code->lookNextChar())){
                    switchState('b');  // state b
                    break;
                }
                // recognize
                present_char = source_code->getNextChar();
                if (isDigit(present_char) || isalpha(present_char)){
                    switchState('a');
                    char_stack += present_char;
                    break;
                }
                // cannot recognize, raise error
                _raiseScanError("Unexpected token");
                break;
            case 'b':  // accepted state, add token to list and clear stack
                addToken(IDENTIFIER, true);
                break;
            case 'c':
                addToken(DELIMITER, false);
                break;
            case 'd':
                addToken(SEPARATOR, true);
                break;
            case 'e':
                addToken(OPERATOR, true);
                break;
            case 'f':
                // outlook
                if (!isSlash(source_code->lookNextChar())){
                    switchState('e');
                    break;
                }
                // recognize
                present_char = source_code->getNextChar();
                if (isSlash(present_char)){
                    switchState('g');
                    char_stack += present_char;
                    break;
                }
            case 'g':
                // outlook
                if (!isLineBreak(source_code->lookNextChar())){
                    present_char = source_code->getNextChar();
                    switchState('g');
                    char_stack += present_char;
                    break;
                }else{
                    // direct recognize
                    switchState('h');
                    break;
                }
            case 'h':
                addToken(COMMENT, false);
                break;
            case 'i':
                // outlook
                if (isSeparator(source_code->lookNextChar())
                || isDelimiter(source_code->lookNextChar())
                || isOperator(source_code->lookNextChar())
                || isColon(source_code->lookNextChar())){
                    switchState('j');
                    break;
                }
                // recognize
                present_char = source_code->getNextChar();
                if (isDigit(present_char)){
                    switchState('i');
                    char_stack += present_char;
                    break;
                }
                _raiseScanError("Unexpected token");
                break;
            case 'j':
                addToken(INTEGER, true);
                break;
            case 'k':
                // outlook
                present_char = source_code->getNextChar();
                if (!isQuotationMark(present_char)){
                    switchState('k');
                    char_stack += present_char;
                    break;
                } else{
                    switchState('l');
                    char_stack += present_char;
                    break;
                }
            case 'l':
                addToken(TEXT, true);
                break;
            case 'm':
                if (isEqualSign(source_code->lookNextChar())){
                    present_char = source_code->getNextChar();
                    switchState('n');
                    char_stack += present_char;
                    break;
                }
                _raiseScanError("Unexpected token");
                break;
            case 'n':
                addToken(ASSIGN, true);
                break;
            default:
                _raiseFatalError("Scanner reached an invalid state");
        }
    }
}

void Scanner:: _raiseScanError(string reason) {
    cerr<<"ERROR: Lexical Error: "<<reason<<" at line "<<source_code->line_num<<" column "<<source_code->column - char_stack.size()<<"."<<endl;
    cerr<<source_code->getLine(source_code->line_num);
    for (int i = 0; i < source_code->column - char_stack.size(); i++) cerr<<' ';
    if (!char_stack.empty()) for (int i = 0; i < char_stack.size(); i++) cerr<<'~';
    cerr<<'^'<<endl;
    cerr<<"Present DFA-Ext(1) information:"<<endl;
    cerr<<"State: "<<state<<endl;
    cerr<<"Char stack: "<<char_stack<<endl;
    cerr<<"Present char: '"<<present_char<<"'"<<endl;
    exit(-1);
}

void Scanner::_raiseFatalError(string reason) {
    cerr<<"FATAL ERROR: Lexical error: "<<reason<<"."<<endl;
    exit(-1);
}


void Scanner::_displayResult() {
    if (token_list.empty()){
        _raiseFatalError("No result for scanner");
    }
    cout << "====================================" << endl;
    cout << "Lexical Analysis Result Table         " << endl;
    cout << "====================================" << endl;
    cout << setiosflags(ios::left)
         << setw(7) << "Line"
         << setw(7) << "Column"
         << setw(14) << "Token"
         << setw(20) << "Value"
         << resetiosflags(ios::left) << endl;
    cout << "------------------------------------" << endl;
    for (const auto &token : token_list) {
        string display_value;
        if (token.type == DELIMITER){
            switch (token.value.c_str()[0]){
                case '\t':
                    display_value = "\\t";
                    break;
                case ' ':
                    display_value = "/w";
                    break;
                case '\n':
                    display_value = "\\n";
                    break;
                case '\r':
                    display_value = "\\r";
                    break;
                default:
                    display_value = "Unknown";
                    break;
            }
        }else{
            display_value = token.value;
        }
        cout<< setiosflags(ios::left)
            << setw(7) <<token.line
            << setw(7) <<token.column
            << setw(14) <<TokenTypeName[token.type]
            << setw(20) <<display_value
            << resetiosflags(ios::left) <<endl;
    }
    cout << "------------------------------------" << endl;
}

vector<Token> Scanner::scan(bool verboseMode) {
    _scan();
    if (verboseMode){
        _displayResult();
    }
    return token_list;
}

Scanner::Scanner(SourceCodeReader* reader) {
    this->source_code = reader;
}
