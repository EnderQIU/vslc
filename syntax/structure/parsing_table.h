//
// Created by enderqiu on 2018/9/19.
//

#ifndef VSLC_PARSING_TABLE_H
#define VSLC_PARSING_TABLE_H

#define TABLE_CELL_MACRO_1(li, col, l_sym, r_sym1) \
    table[Symbol(SymbolType::li)][Symbol(SymbolType::col)] = Production(Symbol(SymbolType::l_sym), {Symbol(SymbolType::r_sym1)});
#define TABLE_CELL_MACRO_2(li, col, l_sym, r_sym1, r_sym2) \
    table[Symbol(SymbolType::li)][Symbol(SymbolType::col)] = Production(Symbol(SymbolType::l_sym), {Symbol(SymbolType::r_sym), Symbol(SymbolType::r_sym2)});
#define TABLE_CELL_MACRO_3(li, col, l_sym, r_sym1, r_sym2, r_sym3) \
    table[Symbol(SymbolType::li)][Symbol(SymbolType::col)] = Production(Symbol(SymbolType::l_sym), {Symbol(SymbolType::r_sym), Symbol(SymbolType::r_sym2), Symbol(SymbolType::r_sym3)});
#define TABLE_CELL_MACRO_4(li, col, l_sym, r_sym1, r_sym2, r_sym3, r_sym4) \
    table[Symbol(SymbolType::li)][Symbol(SymbolType::col)] = Production(Symbol(SymbolType::l_sym), {Symbol(SymbolType::r_sym), Symbol(SymbolType::r_sym2), Symbol(SymbolType::r_sym3), Symbol(SymbolType::r_sym4)});
#define TABLE_CELL_MACRO_5(li, col, l_sym, r_sym1, r_sym2, r_sym3, r_sym4, r_sym5) \
    table[Symbol(SymbolType::li)][Symbol(SymbolType::col)] = Production(Symbol(SymbolType::l_sym), {Symbol(SymbolType::r_sym), Symbol(SymbolType::r_sym2), Symbol(SymbolType::r_sym3), Symbol(SymbolType::r_sym4), Symbol(SymbolType::r_sym5)});
#define TABLE_CELL_MACRO_6(li, col, l_sym, r_sym1, r_sym2, r_sym3, r_sym4, r_sym5, r_sym6) \
    table[Symbol(SymbolType::li)][Symbol(SymbolType::col)] = Production(Symbol(SymbolType::l_sym), {Symbol(SymbolType::r_sym), Symbol(SymbolType::r_sym2), Symbol(SymbolType::r_sym3), Symbol(SymbolType::r_sym4), Symbol(SymbolType::r_sym5), Symbol(SymbolType::r_sym6)});


#include <map>

#include "production.h"

using namespace std;

class ParsingTable {
private:
    map<Symbol, map<Symbol, Production>> table;
public:
    ParsingTable();
    Production getEntry(const Symbol &nonTerminator, const Symbol &terminator);
    bool isErrorEntry(const Symbol &nonTerminator, const Symbol &terminator);
};

Production ParsingTable::getEntry(const Symbol &nonTerminator, const Symbol &terminator) {
    return table.at(nonTerminator).at(terminator);
}

ParsingTable::ParsingTable() {
    // TABLE_CELL_MACRO_N(LINE, COLUMN, LEFT_SYMBOL, RIGHT_SYMBOL_1 ... RIGHT_SYMBOL_N)
    TABLE_CELL_MACRO_1(DOLLAR, DOLLAR, DOLLAR, DOLLAR)
}

bool ParsingTable::isErrorEntry(const Symbol &nonTerminator, const Symbol &terminator) {
    if (table.find(nonTerminator) != table.end()
    && table.at(nonTerminator).find(terminator) != table.at(nonTerminator).end())
         return false;
    else return true;
}

#endif //VSLC_PARSING_TABLE_H
