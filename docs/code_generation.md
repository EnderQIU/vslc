# Part III: IR code generation

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

## Code generation strategy in kaleidoscope
kaleidoscope uses recursive descent method to deal with syntax analysis, 
which means there will be a function for each production. 
In this function, it creates new tree nodes according to the left part of production.
Using Polymorphism, it overwrites codegen method in each subclass of BaseAST to produce IR code.


To implement codegen method, we need to call some functions provided by llvm.


## Our code generation strategy
In the stage of syntax analysis, we choosed to use the method of forecast analysis 
table instead of recursive descent. We thought this method is more effective comparing 
to recursive descent because we don't need to extend syntax analysis part in the future. 
Our syntax analysis procedure also output a syntax tree.


Unlikely to kaleidoscope. our syntax tree only has one kind of node which means we 
won't need to use polymorphism. we plan to call different code generation method 
according to the type of symbol in this three node.


It is likely that our codegen method will look like this:


```cpp
Value *AST::codegen(){
	switch(this->symbol.type){
		case "FUNC":
			return this->funcCodeGen();
		case"PRINT":
			return this->printCodeGen();
		....
		default:
			error();
	}
}
Value *AST::funcCodeGen(){
	some LLVM function call
}
Value *AST::printCodeGen(){
	some LLVM function call
}
...
```


## Code Generation in Shell Mode
Available non-terminators which can be input at a time in the shell are marked with "*".

- - - - - - - - - - - - - - - - - - - - - 
| Non-terminator | Reference            | 
| -------------- | -------------------- | 
| S *            | program              | 
| A *            | function_list        | 
| B *            | function             | 
| C              | parameter_list       | 
| D *            | statement            | 
| E              | variable_list        | 
| F *            | assignment_statement | 
| G              | return_statement     | 
| H *            | print_statement      | 
| I              | null_statement       | 
| J *            | if_statement         | 
| K *            | while_statement      | 
| L *            | block                | 
| M              | expression           | 
| N              | argument_list        | 
| O              | expression_list      | 
| P              | print_list           | 
| Q              | print_item           | 
| R *            | declaration_list     | 
| T              | statement_list       | 
| U *            | declaration          | 
| V              | term                 | 
| W              | factor               | 
- - - - - - - - - - - - - - - - - - - - - 

## Full Code Generation Table
In AST class, we use the public gen() function for outer code gen access to hide details. It will
call the private code gen function by the AST type of itself.

There are 3 kinds of private code generation functions in total:

1. void gen(): Usually in non-terminators which can present as a kind of "statement". It will collect 
 its child nodes' values and insert into the LLVM IR builder.

2. Value gen(): Usually in terminators, just wrap up the value of itself and throw it up.

3. Value gen(Value value1, Value value2, ...): Usually in the expression AST nodes. Collect child 
 nodes' values and pass to its parent node.


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
| Non-terminator & terminator | Reference            | Code Generation Function Prototype |
| --------------------------- | -------------------- | ---------------------------------- |
| S                           | program              | void genS()                        |
| A                           | function_list        |                                    |
| A'                          |                      |                                    |
| B                           | function             |                                    |
| C                           | parameter_list       |                                    |
| D                           | statement            |                                    |
| E                           | variable_list        |                                    |
| E'                          |                      |                                    |
| F                           | assignment_statement |                                    |
| G                           | return_statement     |                                    |
| H                           | print_statement      |                                    |
| I                           | null_statement       |                                    |
| J                           | if_statement         |                                    |
| J'                          |                      |                                    |
| K                           | while_statement      |                                    |
| L                           | block                |                                    |
| M                           | expression           |                                    |
| M'                          |                      |                                    |
| N                           | argument_list        |                                    |
| O                           | expression_list      |                                    |
| O'                          |                      |                                    |
| P                           | print_list           |                                    |
| P'                          |                      |                                    |
| Q                           | print_item           |                                    |
| R                           | declaration_list     |                                    |
| R'                          |                      |                                    |
| T                           | statement_list       |                                    |
| T'                          |                      |                                    |
| U                           | declaration          |                                    |
| V                           | term                 |                                    |
| V'                          |                      |                                    |
| W                           | factor               |                                    |
| W'                          |                      |                                    |
| (                           | L_BRACKET            |                                    |
| )                           | R_BRACKET            |                                    |
| ,                           | COMMA                |                                    |
| +                           | PLUS                 |                                    |
| -                           | MINUS                |                                    |
| *                           | MULTIPLY             |                                    |
| /                           | DIVIDE               |                                    |
| {                           | L_CURLY_BRAC         |                                    |
| }                           | R_CURLY_BRAC         |                                    |
| a                           | FUNC                 |                                    |
| b                           | IDENTIFIER           |                                    |
| c                           | ASSIGN               |                                    |
| d                           | INTEGER              |                                    |
| e                           | PRINT                |                                    |
| f                           | TEXT                 |                                    |
| g                           | RETURN               |                                    |
| h                           | CONTINUE             |                                    |
| i                           | IF                   |                                    |
| j                           | THEN                 |                                    |
| k                           | FI                   |                                    |
| l                           | ELSE                 |                                    |
| m                           | WHILE                |                                    |
| n                           | DO                   |                                    |
| o                           | DONE                 |                                    |
| p                           | VAR                  |                                    |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -