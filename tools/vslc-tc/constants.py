SymbolType = {
    # Inherited from TokenType, removed some non-grammatical token types

    'b': 'IDENTIFIER',
    # Identifier: We regard Keyword as a subclass of identifier
    'a': 'FUNC',
    'e': 'PRINT',
    'g': 'RETURN',
    'h': 'CONTINUE',
    'i': 'IF',
    'j': 'THEN',
    'l': 'ELSE',
    'k': 'FI',
    'm': 'WHILE',
    'n': 'DO',
    'o': 'DONE',
    'p': 'VAR',  # Variable  a special type of identifier

    'c': 'ASSIGN',  # :=

    # OPERATOR,
    # Operator
    '+': 'PLUS',
    '-': 'MINUS',
    '*': 'MULTIPLY',
    '/': 'DIVIDE',

    # SEPARATOR,
    # Separator: {, }, (, ), ,
    '{': 'L_CURLY_BRACE',
    '}': 'R_CURLY_BRACE',
    '(': 'L_BRACKET',
    ')': 'R_BRACKET',
    ',': 'COMMA',

    # Primitive
    'd': 'INTEGER',
    'f': 'TEXT',

    # Non-terminators: We use underline instead of single quote for c++ grammar

    'S': 'S',
    'A': 'A',
    'B': 'B',
    'A_': 'A_',
    'C': 'C',
    'E': 'E',
    'E_': 'E_',
    'D': 'D',
    'F': 'F',
    'M': 'M',
    'M_': 'M_',
    'V': 'V',
    'V_': 'V_',
    'W': 'W',
    'W_': 'W_',
    'N': 'N',
    'O': 'O',
    'P': 'P',
    'P_': 'P_',
    'Q': 'Q',
    'R': 'R',
    'R_': 'R_',
    'T': 'T',
    'T_': 'T_',
    'O_': 'O_',
    'U': 'U',
    'G': 'G',
    'H': 'H',
    'I': 'I',
    'J': 'J',
    'K': 'K',
    'L': 'L',
    'J_': 'J_',

    # Special Symbol

    'ε': 'EPSILON',  # a.k.a ε
    '#': 'HASHTAG',  # a.k.a #
    '$': 'DOLLAR',  # a.k.a $ We use it as the end of input buffer and parsing stack
}
