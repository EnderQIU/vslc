//
// Created by enderqiu on 2018/11/6.
//

#include "engine.h"


LLVMEngine::LLVMEngine() = default;

LLVMEngine * LLVMEngine::instance(){
    static LLVMEngine engineInstance;
    return &engineInstance;
}

void LLVMEngine::save() {
    //TODO backup the LLVM engine instance
}

void LLVMEngine::restore() {
    //TODO Deep copy the members to restore the instance
}

llvm::LLVMContext * LLVMEngine::getContext() {
    return instance()->TheContext;
}

llvm::IRBuilder<> * LLVMEngine::getBuilder() {
    return instance()->Builder;
}

std::unique_ptr<llvm::Module> * LLVMEngine::getModule() {
    return instance()->TheModule;
}

std::map<std::string, llvm::Value *> * LLVMEngine::getNamedValues(){
    return instance()->NamedValues;
}