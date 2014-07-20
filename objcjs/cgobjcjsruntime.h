//
//  objcjsruntime.h
//  objcjs
//
//  Created by Jerry Marino on 7/19/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//

#ifndef objcjs_objcjsruntime_h
#define objcjs_objcjsruntime_h

#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <llvm-c/Core.h>
#include "src/ast.h"

extern llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Function *Function,
                                         const std::string &VarName);
extern llvm::Value *localStringVar(std::string value, llvm::Module *module);

extern llvm::Function *CGObjCJSFunction(size_t numParams,
                                      std::string name,
                                      llvm::Module *mod);

extern llvm::Type *ObjcPointerTy();
extern llvm::Value *ObjcNullPointer();
extern llvm::Value *localStringVar(const char* data, size_t len, llvm::Module *module);

extern std::string asciiStringWithV8String(v8::internal::String *string);

class CGObjCJSRuntime {
public:
    CGObjCJSRuntime(llvm::IRBuilder<> *builder, llvm::Module *module);
    
    llvm::IRBuilder<> *_builder;
    llvm::Module *_module;
    
    llvm::Value *newString(std::string string);
    llvm::Value *newNumber(double value);
    llvm::Value *newNumberWithLLVMValue(llvm::Value *value);
    llvm::Value *doubleValue(llvm::Value *llvmValue);
    llvm::Value *boolValue(llvm::Value *llvmValue);
    llvm::Value *messageSend(llvm::Value *receiver,
                             const char *selector,
                             std::vector<llvm::Value *>ArgsV);
    llvm::Value *messageSend(llvm::Value *receiver,
                             const char *selector,
                             llvm::Value *Arg);
    llvm::Value *messageSend(llvm::Value *receiver,
                             const char *selector);
    llvm::Value *messageSendJSFunction(llvm::Value *instance,
                                       std::vector<llvm::Value *>ArgsV);
    llvm::Value *classNamed(const char *name);   
};


#endif