//
// Created by enderqiu on 2018/11/6.
//

#ifndef VSLC_ENGINE_H
#define VSLC_ENGINE_H

#include <llvm/IR/IRBuilder.h>


class LLVMEngine {
private:
    LLVMEngine();
    llvm::LLVMContext * TheContext;
    llvm::IRBuilder<> * Builder;
    std::unique_ptr<llvm::Module> * TheModule;
    std::map<std::string, llvm::Value *> * NamedValues;
public:
    static LLVMEngine * instance(LLVMEngine * backup=nullptr);
    llvm::LLVMContext * getContext();
    llvm::IRBuilder<> * getBuilder();
    std::unique_ptr<llvm::Module> * getModule();
    std::map<std::string, llvm::Value *> * getNamedValues();

    void save();  // save llvm context state for restoring state if any exception happened
    void restore();  // restore llvm context state if any exception happened
};

#endif //VSLC_ENGINE_H
