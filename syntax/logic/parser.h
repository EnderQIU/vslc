//
// Created by enderqiu on 2018/9/17.
//

#ifndef VSLC_PARSER_H
#define VSLC_PARSER_H

#include "../structure/ast.h"
#include "../structure/input_buffer.h"
#include "../structure/parsing_stack.h"
#include "../structure/production.h"
#include "../structure/parsing_table.h"
#include "../../utils/source_code_reader.h"
#include "../../utils/shortcuts.h"

#include <algorithm>
#include <utility>


extern bool verboseMode, shellMode;
extern void abort();

class Parser {
private:
    InputBuffer inputBuffer;
    ParsingStack parsingStack;
    vector<Production> productions;
    ParsingTable parsingTable;
    Symbol ip;
    Symbol X;
    SourceCodeReader sourceCodeReader;
    AST tree;
    stack<Symbol> possibleRootSymbols;

    void _raiseError(Symbol s);
    void _raiseErrorEntry(Symbol X, Symbol ip);
    AST _parse();
    void _dispalyResult();
public:
    explicit Parser(InputBuffer inputBuffer, SourceCodeReader sourceCodeReader);
    AST parse();
};


#endif //VSLC_PARSER_H
