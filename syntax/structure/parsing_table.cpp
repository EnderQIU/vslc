//
// Created by enderqiu on 2018/9/20.
//

#include "parsing_table.h"


Production ParsingTable::getEntry(const SymbolType &nonTerminator, const SymbolType &terminator) {
    return table.at(nonTerminator).at(terminator);
}

ParsingTable::ParsingTable() {
    // TABLE_CELL_MACRO_N(LINE, COLUMN, LEFT_SYMBOL, RIGHT_SYMBOL_1 ... RIGHT_SYMBOL_N)
    TABLE_CELL_MACRO_1(S, FUNC, S, A);
    TABLE_CELL_MACRO_2(A, FUNC, A, B, A_);
    TABLE_CELL_MACRO_2(A_, FUNC, A_, B, A_);
    TABLE_CELL_MACRO_1(A_, EPSILON, A_, EPSILON);
    TABLE_CELL_MACRO_6(B, FUNC, B, FUNC, IDENTIFIER, L_BRACKET, C, R_BRACKET, D);
    TABLE_CELL_MACRO_1(M_, FUNC, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, EPSILON, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, IDENTIFIER, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, R_BRACKET, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, COMMA, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, RETURN, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, PRINT, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, CONTINUE, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, IF, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, WHILE, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, L_CURLY_BRACE, M_, EPSILON);
    TABLE_CELL_MACRO_3(M_, PLUS, M_, PLUS, V, M_);
    TABLE_CELL_MACRO_3(M_, MINUS, M_, MINUS, V, M_);
    TABLE_CELL_MACRO_1(M_, THEN, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, DO, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, FI, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, ELSE, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, DONE, M_, EPSILON);
    TABLE_CELL_MACRO_1(M_, R_CURLY_BRACE, M_, EPSILON);
    TABLE_CELL_MACRO_1(V_, FUNC, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, EPSILON, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, IDENTIFIER, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, R_BRACKET, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, COMMA, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, RETURN, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, PRINT, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, CONTINUE, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, IF, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, WHILE, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, L_CURLY_BRACE, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, PLUS, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, MINUS, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, THEN, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, DO, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, FI, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, ELSE, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, DONE, V_, EPSILON);
    TABLE_CELL_MACRO_1(V_, R_CURLY_BRACE, V_, EPSILON);
    TABLE_CELL_MACRO_3(V_, MULTIPLY, V_, MULTIPLY, W, V_);
    TABLE_CELL_MACRO_3(V_, DIVIDE, V_, DIVIDE, W, V_);
    TABLE_CELL_MACRO_1(W_, FUNC, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, EPSILON, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, IDENTIFIER, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, R_BRACKET, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, COMMA, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, RETURN, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, PRINT, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, CONTINUE, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, IF, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, WHILE, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, L_CURLY_BRACE, W_, EPSILON);
    TABLE_CELL_MACRO_3(W_, L_BRACKET, W_, L_BRACKET, N, R_BRACKET);
    TABLE_CELL_MACRO_1(W_, PLUS, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, MINUS, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, THEN, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, DO, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, FI, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, ELSE, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, DONE, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, R_CURLY_BRACE, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, MULTIPLY, W_, EPSILON);
    TABLE_CELL_MACRO_1(W_, DIVIDE, W_, EPSILON);
    TABLE_CELL_MACRO_1(P_, FUNC, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, EPSILON, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, IDENTIFIER, P_, EPSILON);
    TABLE_CELL_MACRO_3(P_, COMMA, P_, COMMA, Q, P_);
    TABLE_CELL_MACRO_1(P_, RETURN, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, PRINT, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, CONTINUE, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, IF, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, WHILE, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, L_CURLY_BRACE, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, FI, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, ELSE, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, DONE, P_, EPSILON);
    TABLE_CELL_MACRO_1(P_, R_CURLY_BRACE, P_, EPSILON);
    TABLE_CELL_MACRO_1(C, IDENTIFIER, C, E);
    TABLE_CELL_MACRO_1(C, R_BRACKET, C, EPSILON);
    TABLE_CELL_MACRO_2(E, IDENTIFIER, E, IDENTIFIER, E_);
    TABLE_CELL_MACRO_1(E_, IDENTIFIER, E_, EPSILON);
    TABLE_CELL_MACRO_1(E_, R_BRACKET, E_, EPSILON);
    TABLE_CELL_MACRO_3(E_, COMMA, E_, COMMA, IDENTIFIER, E_);
    TABLE_CELL_MACRO_1(E_, VAR, E_, EPSILON);
    TABLE_CELL_MACRO_1(E_, RETURN, E_, EPSILON);
    TABLE_CELL_MACRO_1(E_, PRINT, E_, EPSILON);
    TABLE_CELL_MACRO_1(E_, CONTINUE, E_, EPSILON);
    TABLE_CELL_MACRO_1(E_, IF, E_, EPSILON);
    TABLE_CELL_MACRO_1(E_, WHILE, E_, EPSILON);
    TABLE_CELL_MACRO_1(E_, L_CURLY_BRACE, E_, EPSILON);
    TABLE_CELL_MACRO_1(D, IDENTIFIER, D, F);
    TABLE_CELL_MACRO_1(D, RETURN, D, G);
    TABLE_CELL_MACRO_1(D, PRINT, D, H);
    TABLE_CELL_MACRO_1(D, CONTINUE, D, I);
    TABLE_CELL_MACRO_1(D, IF, D, J);
    TABLE_CELL_MACRO_1(D, WHILE, D, K);
    TABLE_CELL_MACRO_1(D, L_CURLY_BRACE, D, L);
    TABLE_CELL_MACRO_3(F, IDENTIFIER, F, IDENTIFIER, ASSIGN, M);
    TABLE_CELL_MACRO_2(M, IDENTIFIER, M, V, M_);
    TABLE_CELL_MACRO_2(M, L_BRACKET, M, V, M_);
    TABLE_CELL_MACRO_2(M, INTEGER, M, V, M_);
    TABLE_CELL_MACRO_2(V, IDENTIFIER, V, W, V_);
    TABLE_CELL_MACRO_2(V, L_BRACKET, V, W, V_);
    TABLE_CELL_MACRO_2(V, INTEGER, V, W, V_);
    TABLE_CELL_MACRO_2(W, IDENTIFIER, W, IDENTIFIER, W_);
    TABLE_CELL_MACRO_3(W, L_BRACKET, W, L_BRACKET, M, R_BRACKET);
    TABLE_CELL_MACRO_1(W, INTEGER, W, INTEGER);
    TABLE_CELL_MACRO_1(N, IDENTIFIER, N, O);
    TABLE_CELL_MACRO_1(N, R_BRACKET, N, EPSILON);
    TABLE_CELL_MACRO_1(N, L_BRACKET, N, O);
    TABLE_CELL_MACRO_1(N, INTEGER, N, O);
    TABLE_CELL_MACRO_2(O, IDENTIFIER, O, M, O_);
    TABLE_CELL_MACRO_2(O, L_BRACKET, O, M, O_);
    TABLE_CELL_MACRO_2(O, INTEGER, O, M, O_);
    TABLE_CELL_MACRO_2(P, IDENTIFIER, P, Q, P_);
    TABLE_CELL_MACRO_2(P, L_BRACKET, P, Q, P_);
    TABLE_CELL_MACRO_2(P, INTEGER, P, Q, P_);
    TABLE_CELL_MACRO_2(P, TEXT, P, Q, P_);
    TABLE_CELL_MACRO_1(Q, IDENTIFIER, Q, M);
    TABLE_CELL_MACRO_1(Q, L_BRACKET, Q, M);
    TABLE_CELL_MACRO_1(Q, INTEGER, Q, M);
    TABLE_CELL_MACRO_1(Q, TEXT, Q, TEXT);
    TABLE_CELL_MACRO_1(R, IDENTIFIER, R, R_);
    TABLE_CELL_MACRO_1(R, VAR, R, R_);
    TABLE_CELL_MACRO_1(R, RETURN, R, R_);
    TABLE_CELL_MACRO_1(R, PRINT, R, R_);
    TABLE_CELL_MACRO_1(R, CONTINUE, R, R_);
    TABLE_CELL_MACRO_1(R, IF, R, R_);
    TABLE_CELL_MACRO_1(R, WHILE, R, R_);
    TABLE_CELL_MACRO_1(R, L_CURLY_BRACE, R, R_);
    TABLE_CELL_MACRO_1(R_, IDENTIFIER, R_, EPSILON);
    TABLE_CELL_MACRO_2(R_, VAR, R_, U, R_);
    TABLE_CELL_MACRO_1(R_, RETURN, R_, EPSILON);
    TABLE_CELL_MACRO_1(R_, PRINT, R_, EPSILON);
    TABLE_CELL_MACRO_1(R_, CONTINUE, R_, EPSILON);
    TABLE_CELL_MACRO_1(R_, IF, R_, EPSILON);
    TABLE_CELL_MACRO_1(R_, WHILE, R_, EPSILON);
    TABLE_CELL_MACRO_1(R_, L_CURLY_BRACE, R_, EPSILON);
    TABLE_CELL_MACRO_2(T, IDENTIFIER, T, D, T_);
    TABLE_CELL_MACRO_2(T, RETURN, T, D, T_);
    TABLE_CELL_MACRO_2(T, PRINT, T, D, T_);
    TABLE_CELL_MACRO_2(T, CONTINUE, T, D, T_);
    TABLE_CELL_MACRO_2(T, IF, T, D, T_);
    TABLE_CELL_MACRO_2(T, WHILE, T, D, T_);
    TABLE_CELL_MACRO_2(T, L_CURLY_BRACE, T, D, T_);
    TABLE_CELL_MACRO_2(T_, IDENTIFIER, T_, D, T_);
    TABLE_CELL_MACRO_2(T_, RETURN, T_, D, T_);
    TABLE_CELL_MACRO_2(T_, PRINT, T_, D, T_);
    TABLE_CELL_MACRO_2(T_, CONTINUE, T_, D, T_);
    TABLE_CELL_MACRO_2(T_, IF, T_, D, T_);
    TABLE_CELL_MACRO_2(T_, WHILE, T_, D, T_);
    TABLE_CELL_MACRO_2(T_, L_CURLY_BRACE, T_, D, T_);
    TABLE_CELL_MACRO_1(T_, R_CURLY_BRACE, T_, EPSILON);
    TABLE_CELL_MACRO_1(O_, R_BRACKET, O_, EPSILON);
    TABLE_CELL_MACRO_3(O_, COMMA, O_, COMMA, M, O_);
    TABLE_CELL_MACRO_2(U, VAR, U, VAR, E);
    TABLE_CELL_MACRO_2(G, RETURN, G, RETURN, M);
    TABLE_CELL_MACRO_2(H, PRINT, H, PRINT, P);
    TABLE_CELL_MACRO_1(I, CONTINUE, I, CONTINUE);
    TABLE_CELL_MACRO_5(J, IF, J, IF, M, THEN, D, J_);
    TABLE_CELL_MACRO_5(K, WHILE, K, WHILE, M, DO, D, DONE);
    TABLE_CELL_MACRO_4(L, L_CURLY_BRACE, L, L_CURLY_BRACE, R, T, R_CURLY_BRACE);
    TABLE_CELL_MACRO_1(J_, FI, J_, FI);
    TABLE_CELL_MACRO_3(J_, ELSE, J_, ELSE, D, FI);
}

bool ParsingTable::isErrorEntry(const SymbolType &nonTerminator, const SymbolType &terminator) {
    try {
        getEntry(nonTerminator, terminator);
    } catch (out_of_range &e) {
        return true;
    }
    return false;
}