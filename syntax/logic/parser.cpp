//
// Created by enderqiu on 2018/9/17.
//

#include "parser.h"

AST Parser::_parse() {
    ip = inputBuffer.present();
    X = parsingStack.top();
    
    while(X.type != SymbolType::HASHTAG){
        if (X.isTerminal()) {
            if (X.type == ip.type) {
                parsingStack.pop();
                this->tree.getLowerLeftTNode()->setSymbol(ip);
                inputBuffer.next();
            }
            else{
                _raiseError(X);
            }
        }else if (parsingTable.isErrorEntry(X.type, ip.type)){
            _raiseErrorEntry(X, ip);
        }else{
            Production p = parsingTable.getEntry(X.type, ip.type);
            productions.push_back(p);
            parsingStack.pop();
            AST* temp = this->tree.getLowerLeftNTNode();
            for (int i = 0; i < p.right.size();i++) {
                AST* newAST = new AST(Symbol(p.right.at(i).type));
                temp->addChild(newAST);
            }
            // reverse iterator
            reverse(p.right.begin(), p.right.end());
            for (auto &it : p.right) if (it.type != SymbolType::EPSILON) parsingStack.push(it);
        }
        
        ip = inputBuffer.present();
        X = parsingStack.top();
    }  
    return this->tree;
}

void Parser::_raiseError(Symbol x) {
    cout<<"ERROR: Parser Error at line: "<<ip.line<<" column: "<<ip.column<<endl;
    cout<<sourceCodeReader.getLine(ip.line)<<endl;
    for (int i = 0; i < ip.column - 1; i++) cout<<" ";
    cout<<"^";
    for (int i = 0; i < ip.value.size() - 1; i++) cout<<"~";
    cout<<endl;
    cout<<"Symbol "<<x.getDisplay()<<" (referencing of "<<x.getTypeName()<<") which on top of parsing stack is a terminal."<<endl;
    cout<<"==================="<<endl;
    cout<<"Current parser information:"<<endl;
    cout<<"Input buffer( most recent 5 ): ";
    for (int i = 0; i < 5 && !inputBuffer.is$(); i++){
        cout<<inputBuffer.present().getDisplay();
        inputBuffer.next();
    }
    cout<<endl;
    cout<<"Parsing Stack( most recent 5 ): ";
    for (int i = 0; i < 5 && !parsingStack.empty(); i++){
        cout<<parsingStack.top().getDisplay();
        parsingStack.pop();
    }
    cout<<endl;
    abort(PARSEEXCEPTION);
}

void Parser::_raiseErrorEntry(Symbol X, Symbol ip) {
    cout<<"ERROR: Parser Error at line: "<<ip.line<<" column: "<<ip.column<<endl;
    cout<<sourceCodeReader.getLine(ip.line)<<endl;
    for (int i = 0; i < ip.column - 1; i++) cout<<" ";
    cout<<"^";
    for (int i = 0; i < ip.value.size() - 1; i++) cout<<"~";
    cout<<endl;
    cout<<"M["<<X.getDisplay()<<", "<<ip.getDisplay()<<"] is an error entry."<<endl;
    cout<<"==================="<<endl;
    cout<<"Current parser information:"<<endl;
    cout<<"Input buffer (most recent 5): ";
    for (int i = 0; i < 5 && !inputBuffer.is$(); i++){
        cout<<inputBuffer.present().getDisplay();
        inputBuffer.next();
    }
    cout<<endl;
    cout<<"Parsing Stack (most recent 5): ";
    for (int i = 0; i < 5 && !parsingStack.empty(); i++){
        cout<<parsingStack.top().getDisplay();
        parsingStack.pop();
    }
    cout<<endl;
    abort(PARSEEXCEPTION);
}

void Parser::_dispalyResult() {
    for (Production p: productions) p.display();
}

Parser::Parser(InputBuffer inputBuffer, SourceCodeReader sourceCodeReader) {
    this->inputBuffer = std::move(inputBuffer);
    this->parsingStack = ParsingStack();
    this->parsingStack.push(Symbol(SymbolType::HASHTAG));
    this->parsingStack.push(Symbol(SymbolType::S));
    this->parsingTable = ParsingTable();
    this->sourceCodeReader = sourceCodeReader;
    this->tree = AST(Symbol(SymbolType::S));
}

AST Parser::parse() {
    if (shellMode){
        // Register all possible root symbols. See docs/code_generations.md #Code Generation in Shell Mode
        possibleRootSymbols.push(Symbol(SymbolType::S));
        possibleRootSymbols.push(Symbol(SymbolType::A));
        possibleRootSymbols.push(Symbol(SymbolType::B));
        possibleRootSymbols.push(Symbol(SymbolType::D));
        possibleRootSymbols.push(Symbol(SymbolType::F));
        possibleRootSymbols.push(Symbol(SymbolType::H));
        possibleRootSymbols.push(Symbol(SymbolType::J));
        possibleRootSymbols.push(Symbol(SymbolType::K));
        possibleRootSymbols.push(Symbol(SymbolType::L));
        possibleRootSymbols.push(Symbol(SymbolType::T));
        possibleRootSymbols.push(Symbol(SymbolType::R));
        possibleRootSymbols.push(Symbol(SymbolType::U));

        // try all possible syntax trees
        AST rootAST;
        while(!possibleRootSymbols.empty()){
            // reset the parsing stack and the input buffer
            this->parsingStack.clear();
            this->sourceCodeReader.resetOffset();
            this->inputBuffer.reset();
            this->parsingStack.push(Symbol(SymbolType::HASHTAG));
            this->parsingStack.push(possibleRootSymbols.top());
            this->parsingTable = ParsingTable();
            this->tree = AST(possibleRootSymbols.top());
            try {
                rootAST = _parse();
            }
            catch (...){
                possibleRootSymbols.pop();  // pop the possible invalid symbol
                continue;
            }
            break;
        }
        if (possibleRootSymbols.empty()){
            // No valid symbols left
            cout << "ERROR: Syntax Error: No valid root node found." << endl;
        }else{
            // successfully parsed with a root symbol
            if (verboseMode) _dispalyResult();
            return rootAST;
        }
    }
    AST rootAST = _parse();
    if (verboseMode) _dispalyResult();
    return rootAST;
}
