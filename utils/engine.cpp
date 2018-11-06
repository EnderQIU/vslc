//
// Created by enderqiu on 2018/11/6.
//

#include "engine.h"


LLVMEngine::LLVMEngine() = default;

LLVMEngine * LLVMEngine::instance(LLVMEngine * backup){
    static LLVMEngine engineInstance;
    //TODO backup the instance
//    if (backup != nullptr){
//        engineInstance = backup;
//    }
    return &engineInstance;
}

void LLVMEngine::save() {

}

void LLVMEngine::restore() {
    //TODO Deep copy the members
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