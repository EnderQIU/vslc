# Part II: VSL Syntax Analysis Design

## VSL Grammar (in yacc format)
```yacc
program	: function_list
		;
function_list : function
		| function_list function
		;
function : FUNC VARIABLE '(' parameter_list ')' statement
		;
parameter_list : variable_list
		| ε
		;
variable_list : VARIABLE
		| variable_list ',' VARIABLE
		;
statement : assignment_statement
		| return_statement
		| print_statement
		| null_statement
		| if_statement
		| while_statement
		| block
		;
assignment_statement : VARIABLE ASSIGN expression
		;
expression : expression '+' expression
		| expression '-' expression
		| expression '*' expression
		| expression '/' expression
		| '-' expression
		| '(' expression ')'
		| INTEGER
		| VARIABLE
		| VARIABLE '(' argument_list ')'
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
declaration_list:
		| declaration_list declaration
		;
declaration : VAR variable_list
		;
statement_list : statement
		| statement_list statement
		;
```

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

## LL(1) Parsing

1. Elimination of Left Recursion



2. Left Factoring

3.