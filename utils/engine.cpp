//
// Created by enderqiu on 2018/11/6.
//

#include "engine.h"


LLVMEngine::LLVMEngine() = default;

LLVMEngine * LLVMEngine::GetInstance(){
    if (engineInstance == nullptr){
        engineInstance = new LLVMEngine();
        engineInstance->Builder = new llvm::IRBuilder<>(*(engineInstance->TheContext));  // set the builder's context
    }
    return engineInstance;
}

void LLVMEngine::save() {
    engineBackup = new LLVMEngine();
    //TODO Deep copy the members
    engineBackup->TheContext = engineInstance->TheContext;
    engineBackup->Builder = engineInstance->Builder;
    engineBackup->TheModule = engineInstance->TheModule;
    engineBackup->NamedValues = engineInstance->NamedValues;
}

void LLVMEngine::restore() {
    //TODO Deep copy the members
    engineInstance = engineBackup;
}

llvm::LLVMContext * LLVMEngine::getContext() {
    return engineInstance->TheContext;
}

llvm::IRBuilder<> * LLVMEngine::getBuilder() {
    return engineInstance->Builder;
}

std::unique_ptr<llvm::Module> * LLVMEngine::getModule() {
    return engineInstance->TheModule;
}

std::map<std::string, llvm::Value *> * LLVMEngine::getNamedValues(){
    return engineInstance->NamedValues;
}