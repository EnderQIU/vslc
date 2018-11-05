//
// Created by enderqiu on 2018/11/6.
//

#ifndef VSLC_ENGINE_H
#define VSLC_ENGINE_H

#include <llvm/IR/IRBuilder.h>


llvm::LLVMContext TheContext;
llvm::IRBuilder<> Buider(TheContext);
std::unique_ptr<llvm::Module> TheModule;
std::map<std::string, llvm::Value *> NamedValues;

#endif //VSLC_ENGINE_H
