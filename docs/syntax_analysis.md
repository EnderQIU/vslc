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
A -> B | Ab
B -> ab(C)D
C -> E | ε
E -> b | E,b
D -> F | G | H | I | J | K | L
F -> bcL
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
- `A -> B | Ab`
```production
A  -> BA'
A' -> bA' | ε
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
J  -> J'
J' -> iMjD | iMjDlDk
```

- `W -> (M) | d | b | b(N)`
```production
W  -> (M) | d | bW'
W' -> (N) | ε
```

4. FIRST & FOLLOW sets
We use first-follow package to generate FIRST & FOLLOW. Tools are stored in tools/vslc-ff/.

- Final grammar
```production
S -> A
A  -> BA'
A' -> bA' | ε
B -> ab(C)D
C -> E | ε
E  -> bE'
E' -> ,bE' | ε
D -> F | G | H | I | J | K | L
F -> bcL
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

- Instruction
```bash
cd tools/vslc-ff/
npm install
node grammar.js
```

5. Calculate SELECT Set

6. Define Production Class
```production
class Production{
	Token left;
	List<Token> right;
}

//eg.
//A -> ab
Token A , a , b;
Production p = new Production();
p.left=A;
p.right.push(a);
p.right.push(b);
```

7. Fill In Predicting Analysis Table
```production
Token terminal[?];
Token nonTerminal[?];
production[terminal.size()][nonTerminal.size()] table;

//eg.
terminal = {A , B}
nonTerminal = {a , b , c}
IF
SELECT(A -> ab) = {a , c}
Then 
-------------------------------------------------
|	  	a    	b    	c    	ε	|
|  A  		A->ab		A->ab		|
|  B						|
-------------------------------------------------

Production p;
table[0][0]=p;
table[0][2]=p;
```

8. Define Abstract TreeNode
```production
Class TreeNode{
	Token origin; 
	List<TreeNode> children;
	//return the nonTerminal TreeNode in children which has the lowest index
	public getLeftNonTerminal();
}
```

9. Algorithm Graph
- `see syntax_analysis_algrorithm.jpg`




