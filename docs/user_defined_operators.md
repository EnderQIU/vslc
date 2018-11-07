# Part VI: User-defined Operators

## Introduction

​    The syntax definition of vsl does not support user-defined operators, therefore this document only explains how to make Kaleidoscope implement user-defined operators.

​    Kaleidoscope now is a fully functional language，but it doesn't have many useful operators (like division, logical negation, or even any comparisons besides less-than).  In C++, we are only allowed to redefine existing operators, we can’t pro-grammatically change the grammar, introduce new operators or change precedence levels, we will add these capabilities to Kaleidoscope.

​    The two specific features we’ll add are programmable unary operators (right now, Kaleidoscope has no unary operators at all) as well as binary operators. 

## Binary Operators

​    Adding support for user-defined binary operators is pretty simple with our current framework,  the steps are as follows:

- Add support for the binary keyword to the lexer

- Extend the `PrototypeAST` AST node to represent the operator definition function 

- Extend `ParsePrototype` function to parse the operator definition function

- Modify `BinaryExprAST`'s codegen function to generate IR code

- Modify `FunctionAST`'s codegen function to register new operator in the precedence table

​     By using operator precedence parsing, it is very easy to allow the programmer to introduce new operators into the grammar: the grammar is dynamically extensible as the JIT runs.

## Unary Operators

   Since we don’t currently support unary operators in the Kaleidoscope language, we’ll need to add everything to support them, the steps are as follows:

- Add support for the unary keywords to the lexer
- Add `UnaryExprAST` node Inherited from `ExprAST` to represent unary operations
- Add `ParseUnary` function to parse a unary operator
- Extend `ParsePrototype` function to parse the operator definition function

​    This code is similar to, but simpler than, the code for binary operators. It is simpler primarily because it doesn't need to handle any predefined operators.

## Kicking the Tires

​    Now we have made Kaleidoscope implement user-defined operators, with this, we can do a lot of interesting things, including I/O, math, and a bunch of other things. For example, we can now add a nice sequencing operator as below:

```
ready> extern printd(x);
Read extern:
declare double @printd(double)

ready> def binary : 1 (x y) 0;  # Low-precedence operator that ignores operands.
...
ready> printd(123) : printd(456) : printd(789);
123.000000
456.000000
789.000000
Evaluated to 0.000000
```