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

##Code generation strategy in kaleidoscope
kaleidoscope uses recursive descent method to deal with syntax analysis, 
which means there will be a function for each production. 
In this function, it creates new tree nodes according to the left part of production.
Using Polymorphism, it overwrites codegen method in each subclass of BaseAST to produce IR code.

To implement codegen method, we need to call some functions provided by llvm.

##Our code generation strategy
In the stage of syntax analysis, we choosed to use the method of forecast analysis 
table instead of recursive descent. We thought this method is more effective comparing 
to recursive descent because we don`t need to extend syntax analysis part in the future. 
Our syntax analysis procedure also output a syntax tree.

Unlikly to kaleidoscope. our syntax tree only has one kind of node which means we 
won`t need to use polymorphism. we plan to call different code generation method 
according to the type of symbol in this three node.

It is likly that our codegen method will look like this:

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