//
// Created by enderqiu on 2018/9/17.
//

#include "parser.h"

AST* Parser::_parse() {
    Symbol ip = inputBuffer->present();
    Symbol X = parsingStack->top();
    while(!parsingStack->empty()){
        if (X.type == ip.type){
            parsingStack->pop();
        }
        else if (X.isTerminal()){
            _raiseError();
        }
        else if (parsingTable.isErrorEntry(X.type, ip.type)){
            _raiseErrorEntry();
        }
        else{
            Production p = parsingTable.getEntry(X.type, ip.type);
            productions.push_back(p);
            parsingStack->pop();
            for (const Symbol &s: p.right) parsingStack->push(s);
        }
        X = parsingStack->top();
    }
    return new AST();
}

void Parser::_raiseError() {
    cerr<<"ERROR: Parser Error: X is a terminal."<<endl;
    exit(-1);
}

void Parser::_raiseErrorEntry() {
    cerr<<"ERROR: Parser Error: M[X, a] is an error entry."<<endl;
}

void Parser::_dispalyResult() {
    for (Production p: productions) p.display();
}

Parser::Parser(InputBuffer *inputBuffer) {
    this->inputBuffer = inputBuffer;
    this->parsingStack = new ParsingStack();
    this->parsingTable = ParsingTable();
}

AST* Parser::parse(bool verboseMode) {
    AST* rootAST = _parse();
    if (verboseMode) _dispalyResult();
    return rootAST;
}
