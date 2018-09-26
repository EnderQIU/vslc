# Part II: VSL Syntax Analysis Design

## Position of this part

```ascii

+------------+          +------------+          +--------------+
|            |  Token   |            |  Syntax  |              |  IR
|  Scanner   +--------> |   Parser   +--------> |Code Generator+------>
|            |          |            |   Tree   |              |
+------------+          +-----+------+          +--------------+
                              ^
           ^                  |                     ^
           |                  ^                     |
           |            +-----+------+              |
           |            |   Symbol   |              |
           +----------> |   Table    | <------------+
                        +------------+

```


## VSL Grammar (in yacc format)
```yacc
program	: function_list
		;
function_list : function
		| function_list function
		;
function : FUNC IDENTIFIER '(' parameter_list ')' statement
		;
parameter_list : variable_list
		| ε
		;
variable_list : IDENTIFIER
		| variable_list ',' IDENTIFIER
		;
statement : assignment_statement
		| return_statement
		| print_statement
		| null_statement
		| if_statement
		| while_statement
		| block
		;
assignment_statement : IDENTIFIER ASSIGN expression
		;
expression : expression '+' expression
		| expression '-' expression
		| expression '*' expression
		| expression '/' expression
		| '-' expression
		| '(' expression ')'
		| INTEGER
		| IDENTIFIER
		| IDENTIFIER '(' argument_list ')'
		;
argument_list : ε
		| expression_list
		;
expression_list	: expression
		| expression_list ',' expression
		;
print_statement	: PRINT print_list
		;
print_list : print_item
		| print_list ',' print_item
		;
print_item : expression
		| TEXT
		;
return_statement: RETURN expression
		;			;
null_statement : CONTINUE
		;
if_statement : IF expression THEN statement FI
		| IF expression THEN statement
		  ELSE statement FI
		;
while_statement : WHILE expression DO statement DONE
		;
block	 : '{' declaration_list statement_list '}'
		;
declaration_list: ε
		| declaration_list declaration
		;
declaration : VAR variable_list
		;
statement_list : statement
		| statement_list statement
		;
```

+ Explanation: `parameter_list` is the function parameter list when declaring a function. `argument_list` is 
the function parameter list when calling a function

### Simplify the VSL Grammar
+ Upper case letter represents a non-terminator, lower case letter represents a terminator. Just the same as the example
of 《Compilers - Principles, Techniques, &Tools》, ε means empty.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
| Non-terminator | Reference            | Terminator | Reference    | 
| -------------- | -------------------- | ---------- | ------------ | 
| S              | program              | (          | L_BRACKET    | 
| A              | function_list        | )          | R_BRACKET    | 
| B              | function             | ,          | COMMA        | 
| C              | parameter_list       | +          | PLUS         | 
| D              | statement            | -          | MINUS        | 
| E              | variable_list        | *          | MULTIPLY     | 
| F              | assignment_statement | /          | DIVIDE       | 
| G              | return_statement     | {          | L_CURLY_BRAC | 
| H              | print_statement      | }          | R_CURLY_BRAC | 
| I              | null_statement       | a          | FUNC         | 
| J              | if_statement         | b          | IDENTIFIER   | 
| K              | while_statement      | c          | ASSIGN       | 
| L              | block                | d          | INTEGER      | 
| M              | expression           | e          | PRINT        | 
| N              | argument_list        | f          | TEXT         | 
| O              | expression_list      | g          | RETURN       | 
| P              | print_list           | h          | CONTINUE     | 
| Q              | print_item           | i          | IF           | 
| R              | declaration_list     | j          | THEN         | 
| T              | statement_list       | k          | FI           | 
| U              | declaration          | l          | ELSE         | 
| V              | term                 | m          | WHILE        | 
| W              | factor               | n          | DO           | 
|                |                      | o          | DONE         | 
|                |                      | p          | VAR          | 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
+ Productions
```
S -> A
A -> B | AB
B -> ab(C)D
C -> E | ε
E -> b | E,b
D -> F | G | H | I | J | K | L
F -> bcM
M -> M+M | M-M | M*M | M/M | -M | (M) | d | b | b(N)
N -> ε | O
O -> M | O,M
H -> eP
P -> Q | P,Q
Q -> M | f
G -> gM
I -> h
J -> iMjDk | iMjDlDk
K -> mMnDo
L -> {RT}
R -> ε | RU
U -> pE
T -> D | TD
```
----------------

## LL(1) Parsing
1. Fix priority of arithmetic

For production `M -> M+M | M-M | M*M | M/M | -M | (M) | d | b | b(N)`
+ Add two non-terminators V: term, W: factor

```production
M -> M+V | M-V | V
V -> V*W | V/W | W
W -> (M) | d | b | b(N)
```

2. Elimination of Left Recursion
- `A -> B | AB`
```production
A  -> BA'
A' -> BA' | ε
```

- `E -> b | E,b`
```production
E  -> bE'
E' -> ,bE' | ε
```

- `O -> M | O,M`
```production
O  -> MO'
O' -> ,MO' | ε
```

- `P -> Q | P,Q`
```production
P  -> QP'
P' -> ,QP' | ε
```

- `R -> ε | RU`
```production
R  -> R'
R' -> UR' | ε
```

- `T -> D | TD`
```production
T  -> DT'
T' -> DT' | ε
```

- `M -> M+V | M-V | V`
```production
M  -> VM'
M' -> +VM' | -VM' | ε
```

- `V -> V*W | V/W | W`
```production
V  -> WV'
V' -> *WV' | /WV' | ε
```


3. Left Factoring

- `J -> iMjDk | iMjDlDk`
```production
J  -> iMjDJ'
J' -> k | lDk
```

- `W -> (M) | d | b | b(N)`
```production
W  -> (M) | d | bW'
W' -> (N) | ε
```

4. Algorithm Model: Table-driven Predictive Parser
```ascii
             +-------------+
Input Buffer:|a|b|(|)|{|}|#|
             ++------------+
              ^
              |
Parsing+-+   ++------------+           +--------------------+
Stack: | +<--+             +--> Output:|class AST           |
       | |   |   Predict   |           +--------------------+
       |S|   |   Parsing   |           |ASTTYPE:type        |
       +-+   |   Program   |           |Vector<AST>:children|
       |#|   |             |           |Token?:token        |
       +-+   ++------------+           +--------------------+
              |
              v
             ++------------+
             |   Parsing   |
             |    Table    |
             +-------------+

```

So at first, we need to do the following preparation stuff:
- Implement the abstract input buffer, parsing stack and parsing table into cpp classes. See code in [parser/structure/](https://github.com/EnderQIU/vslc/parser/structure/)
- Calculate FIRST & FOLLOW sets.
- Generate Parsing Table.
- Import the calculated parsing table into cpp `ParsingTable` class's constructor.

5. Calculate FIRST & FOLLOW sets
We use first-follow package to generate FIRST & FOLLOW. Tools are stored in tools/vslc-ff/.

- Usage Instruction
```bash
cd tools/vslc-ff/
npm install
node grammar.js > result.txt
```
- Result
See results in [select.txt](https://github.com/EnderQIU/vslc/blob/master/tools/vslc-ff/select.txt)

- Final grammar
```production
S -> A
A  -> BA'
A' -> BA' | ε
B -> ab(C)D
C -> E | ε
E  -> bE'
E' -> ,bE' | ε
D -> F | G | H | I | J | K | L
F -> bcM
M  -> VM'
M' -> +VM' | -VM' | ε
V  -> WV'
V' -> *WV' | /WV' | ε
W  -> (M) | d | bW'
W' -> (N) | ε
N -> ε | O
O  -> MO'
O' -> ,MO' | ε
H -> eP
P  -> QP'
P' -> ,QP' | ε
Q -> M | f
G -> gM
I -> h
J  -> J'
J' -> iMjD | iMjDlDk
K -> mMnDo
L -> {RT}
R  -> R'
R' -> UR' | ε
U -> pE
T  -> DT'
T' -> DT' | ε
```

6. Generate Parsing Table
We generated the parsing table following the algorithm on the book, which implements in Python. See code in 
[vslc-pt.py](https://github.com/EnderQIU/vslc/blob/master/tools/vslc-pt/vslc-pt.py)

- Usage Instruction
```sh
cd tools/vslc-pt/
virtualenv venv -p python3
source ./venv/bin/activate
pip install -r requirements.pip
python vslc-pt.py > result.txt
```

- Result
# Parsing Table
|   |     (     |    )    |     *      |     +      |     ,      |     -      |     /      |      a      |     b     |    d     |     e     |    f     |     g     |     h     |      i      |    j    |    k    |     l     |     m      |    n    |    o    |     p     |     {     |    }    |    #    |
|---|-----------|---------|------------|------------|------------|------------|------------|-------------|-----------|----------|-----------|----------|-----------|-----------|-------------|---------|---------|-----------|------------|---------|---------|-----------|-----------|---------|---------|
|A  |           |         |            |            |            |            |            | A -> BA'    |           |          |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|A' |           |         |            |            |            |            |            | A' -> BA'   |           |          |           |          |           |           |             |         |         |           |            |         |         |           |           |         | A' -> ε |
|B  |           |         |            |            |            |            |            | B -> ab(C)D |           |          |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|C  |           | C -> ε  |            |            |            |            |            |             | C -> E    |          |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|D  |           |         |            |            |            |            |            |             | D -> F    |          | D -> H    |          | D -> G    | D -> I    | D -> J      |         |         |           | D -> K     |         |         |           | D -> L    |         |         |
|E  |           |         |            |            |            |            |            |             | E -> bE'  |          |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|E' |           | E' -> ε |            |            | E' -> ,bE' |            |            |             | E' -> ε   |          | E' -> ε   |          | E' -> ε   | E' -> ε   | E' -> ε     |         |         |           | E' -> ε    |         |         | E' -> ε   | E' -> ε   |         |         |
|F  |           |         |            |            |            |            |            |             | F -> bcM  |          |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|G  |           |         |            |            |            |            |            |             |           |          |           |          | G -> gM   |           |             |         |         |           |            |         |         |           |           |         |         |
|H  |           |         |            |            |            |            |            |             |           |          | H -> eP   |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|I  |           |         |            |            |            |            |            |             |           |          |           |          |           | I -> h    |             |         |         |           |            |         |         |           |           |         |         |
|J  |           |         |            |            |            |            |            |             |           |          |           |          |           |           | J -> iMjDJ' |         |         |           |            |         |         |           |           |         |         |
|J' |           |         |            |            |            |            |            |             |           |          |           |          |           |           |             |         | J' -> k | J' -> lDk |            |         |         |           |           |         |         |
|K  |           |         |            |            |            |            |            |             |           |          |           |          |           |           |             |         |         |           | K -> mMnDo |         |         |           |           |         |         |
|L  |           |         |            |            |            |            |            |             |           |          |           |          |           |           |             |         |         |           |            |         |         |           | L -> {RT} |         |         |
|M  | M -> VM'  |         |            |            |            |            |            |             | M -> VM'  | M -> VM' |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|M' |           | M' -> ε |            | M' -> +VM' | M' -> ε    | M' -> -VM' |            | M' -> ε     | M' -> ε   |          | M' -> ε   |          | M' -> ε   | M' -> ε   | M' -> ε     | M' -> ε | M' -> ε | M' -> ε   | M' -> ε    | M' -> ε | M' -> ε |           | M' -> ε   | M' -> ε | M' -> ε |
|N  | N -> O    | N -> ε  |            |            |            |            |            |             | N -> O    | N -> O   |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|O  | O -> MO'  |         |            |            |            |            |            |             | O -> MO'  | O -> MO' |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|O' |           | O' -> ε |            |            | O' -> ,MO' |            |            |             |           |          |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|P  | P -> QP'  |         |            |            |            |            |            |             | P -> QP'  | P -> QP' |           | P -> QP' |           |           |             |         |         |           |            |         |         |           |           |         |         |
|P' |           |         |            |            | P' -> ,QP' |            |            | P' -> ε     | P' -> ε   |          | P' -> ε   |          | P' -> ε   | P' -> ε   | P' -> ε     |         | P' -> ε | P' -> ε   | P' -> ε    |         | P' -> ε |           | P' -> ε   | P' -> ε | P' -> ε |
|Q  | Q -> M    |         |            |            |            |            |            |             | Q -> M    | Q -> M   |           | Q -> f   |           |           |             |         |         |           |            |         |         |           |           |         |         |
|R  |           |         |            |            |            |            |            |             | R -> R'   |          | R -> R'   |          | R -> R'   | R -> R'   | R -> R'     |         |         |           | R -> R'    |         |         | R -> R'   | R -> R'   |         |         |
|R' |           |         |            |            |            |            |            |             | R' -> ε   |          | R' -> ε   |          | R' -> ε   | R' -> ε   | R' -> ε     |         |         |           | R' -> ε    |         |         | R' -> UR' | R' -> ε   |         |         |
|S  |           |         |            |            |            |            |            | S -> A      |           |          |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|T  |           |         |            |            |            |            |            |             | T -> DT'  |          | T -> DT'  |          | T -> DT'  | T -> DT'  | T -> DT'    |         |         |           | T -> DT'   |         |         |           | T -> DT'  |         |         |
|T' |           |         |            |            |            |            |            |             | T' -> DT' |          | T' -> DT' |          | T' -> DT' | T' -> DT' | T' -> DT'   |         |         |           | T' -> DT'  |         |         |           | T' -> DT' | T' -> ε |         |
|U  |           |         |            |            |            |            |            |             |           |          |           |          |           |           |             |         |         |           |            |         |         | U -> pE   |           |         |         |
|V  | V -> WV'  |         |            |            |            |            |            |             | V -> WV'  | V -> WV' |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|V' |           | V' -> ε | V' -> *WV' | V' -> ε    | V' -> ε    | V' -> ε    | V' -> /WV' | V' -> ε     | V' -> ε   |          | V' -> ε   |          | V' -> ε   | V' -> ε   | V' -> ε     | V' -> ε | V' -> ε | V' -> ε   | V' -> ε    | V' -> ε | V' -> ε |           | V' -> ε   | V' -> ε | V' -> ε |
|W  | W -> (M)  |         |            |            |            |            |            |             | W -> bW'  | W -> d   |           |          |           |           |             |         |         |           |            |         |         |           |           |         |         |
|W' | W' -> (N) | W' -> ε | W' -> ε    | W' -> ε    | W' -> ε    | W' -> ε    | W' -> ε    | W' -> ε     | W' -> ε   |          | W' -> ε   |          | W' -> ε   | W' -> ε   | W' -> ε     | W' -> ε | W' -> ε | W' -> ε   | W' -> ε    | W' -> ε | W' -> ε |           | W' -> ε   | W' -> ε | W' -> ε |

7. Import Parsing Table into Cpp Source Code
For convenience, we wrote a python script to generate cpp source code which convert parsing table into `ParsingTable` class constructor statement.
See our code in [vslc-tc.py](https://github.com/EnderQIU/vslc/blob/master/tools/vslc-tc/vslc-tc.py)

8. Complete the logic part -- the Predict Parsing Program
Fake code from the book:
```fake code
set ip to point to the first symbol of w ;
set X to the top stack symbol;
while ( X =I=- $ ) { /* stack is not empty */
    if( X is a ) pop the stack and advance ip;
    else if ( X is a terminal ) error(O);
    else if ( M[X, a] is an error entry ) error(O);
    else if ( M[X, a] = X -> Y1 Y2 ... Yk){
        forward the ip;
        output the production X -> Y1 Y2 ... Yk;
        pop the stack;
        push Yk, Yk-1, ..., Y1 onto the stack , with Y1 on top;
    }
    set X on the top of stack symbol;
}
```
See implementation in [parser.cpp](https://github.com/EnderQIU/vslc/blob/master/syntax/logic/parser.cpp), method `_parse()`.

9. Generate the Abstract Syntax Tree