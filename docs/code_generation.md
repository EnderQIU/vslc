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
| S                           | program              | void gen<void> ()                  |
| A                           | function_list        | void gen<void> ()                  |
| A'                          |                      | void gen<void> ()                  |
| B                           | function             | void gen<void> ()                  |
| C                           | parameter_list       | Value* gen<Value*> ()              |
| D                           | statement            | void gen<void> ()                  |
| E                           | variable_list        | void gen<void> ()                  |
| E'                          |                      | void gen<void> ()                  |
| F                           | assignment_statement | void gen<void> ()                  |
| G                           | return_statement     | void gen<void> ()                  |
| H                           | print_statement      | void gen<void> ()                  |
| I                           | null_statement       | void gen<void> ()                  |
| J                           | if_statement         | void gen<void> ()                  |
| J'                          |                      | void gen<void> ()                  |
| K                           | while_statement      | void gen<void> ()                  |
| L                           | block                | void gen<void> ()                  |
| M                           | expression           | Value* gen<Value*>()               |
| M'                          |                      | Value* gen<Value*>()               |
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
| (                           | L_BRACKET            | Value* gen<Value*> ()              |
| )                           | R_BRACKET            | Value* gen<Value*> ()              |
| ,                           | COMMA                | Value* gen<Value*> ()              |
| +                           | PLUS                 | Value* gen<Value*> ()              |
| -                           | MINUS                | Value* gen<Value*> ()              |
| *                           | MULTIPLY             | Value* gen<Value*> ()              |
| /                           | DIVIDE               | Value* gen<Value*> ()              |
| {                           | L_CURLY_BRAC         | Value* gen<Value*> ()              |
| }                           | R_CURLY_BRAC         | Value* gen<Value*> ()              |
| a                           | FUNC                 | Value* gen<Value*> ()              |
| b                           | IDENTIFIER           | Value* gen<Value*> ()              |
| c                           | ASSIGN               | Value* gen<Value*> ()              |
| d                           | INTEGER              | Value* gen<Value*> ()              |
| e                           | PRINT                | Value* gen<Value*> ()              |
| f                           | TEXT                 | Value* gen<Value*> ()              |
| g                           | RETURN               | Value* gen<Value*> ()              |
| h                           | CONTINUE             | Value* gen<Value*> ()              |
| i                           | IF                   | Value* gen<Value*> ()              |
| j                           | THEN                 | Value* gen<Value*> ()              |
| k                           | FI                   | Value* gen<Value*> ()              |
| l                           | ELSE                 | Value* gen<Value*> ()              |
| m                           | WHILE                | Value* gen<Value*> ()              |
| n                           | DO                   | Value* gen<Value*> ()              |
| o                           | DONE                 | Value* gen<Value*> ()              |
| p                           | VAR                  | Value* gen<Value*> ()              |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -