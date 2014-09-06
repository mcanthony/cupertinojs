//
//  cujsllvmutils.cpp
//  cujs
//
//  Created by Jerry Marino on 8/28/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//
#include <llvm-c/Core.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/CFG.h>
#include <llvm/Transforms/Utils/BasicBlockUtils.h>

#include "cujsllvmutils.h"

using namespace llvm;

unsigned cujs::BasicBlockGetNumPredecessors(llvm::BasicBlock *BB) {
    //FIXME : is there a better way to get
    // the number of predecessors
    unsigned nPred = 0;
    for (auto begin = pred_begin(BB), end = pred_end(BB); begin != end; ++begin) {
        nPred++;
    }
    
    return nPred;
}

void CleanupBasicBlock(BasicBlock *BB){
    std::vector<llvm::BasicBlock *>removedSuccessorsOfMore;
    
    if(BB->getParent()){
        TerminatorInst *BBTerm = BB->getTerminator();
        // Loop through all of our successors and make sure they know that one
        // of their predecessors is going away.
        for (unsigned i = 0, e = BBTerm->getNumSuccessors(); i != e; ++i){
            BBTerm->getSuccessor(i)->removePredecessor(BB);
        }
        
        // Zap all the instructions in the block.
        while (!BB->empty()) {
            Instruction &I = BB->back();
            // If this instruction is used, replace uses with an arbitrary value.
            // Because control flow can't get here, we don't care what we replace the
            // value with.  Note that since this block is unreachable, and all values
            // contained within it must dominate their uses, that all uses will
            // eventually be removed (they are themselves dead).
            if (!I.use_empty())
            I.replaceAllUsesWith(UndefValue::get(I.getType()));
            BB->getInstList().pop_back();
            I.dropAllReferences();
        }
        
        BB->dropAllReferences();
        BB->eraseFromParent();
    }
}
#include <set>

void cujs::FunctionCleanupInstructionsAfterTerminator(llvm::Function *function){
    std::set<llvm::BasicBlock *>removedSuccessorsOf;

    for (llvm::Function::iterator BB = function->begin(), BBE = function->end(); BB != BBE; ++BB){
        
        llvm::Instruction *terminator = NULL;
        for (llvm::BasicBlock::iterator I = BB->begin(), IE = BB->end(); I != IE; ++I){
            llvm::Instruction *instruction = I;
            if (!terminator &&
                (llvm::ReturnInst::classof(instruction) || llvm::BranchInst::classof(instruction))){
                terminator = instruction;
            } else if (terminator) {
               
                //Remove all instructions after the terminator
                //TODO: fix prototype kludge
                while (instruction
                       && instruction != IE
                       && instruction != terminator
                       ) {
                    auto next = I++;
                    
                    auto shouldDropAllReferences = instruction->getNumUses() == 1;
                    if (shouldDropAllReferences) {
                        if (llvm::BranchInst::classof(instruction)) {
                            //Keep track of all the successors we removed a reference to
                            auto numSuccessors =  ((llvm::BranchInst *)instruction)->getNumSuccessors();
                            
                            for (unsigned i = 0; i < numSuccessors; i++){
                                auto nestedBB = ((llvm::BranchInst *)instruction)->getSuccessor(i);
                                removedSuccessorsOf.insert(nestedBB);
                            }
                        }
                        
                        instruction->replaceAllUsesWith(UndefValue::get(instruction->getType()));
                        BB->getInstList().pop_back();
                        instruction->dropAllReferences();
                        instruction->eraseFromParent();
                    } else if (instruction->getParent() && !instruction->getNumUses()) {
                        instruction->replaceAllUsesWith(UndefValue::get(instruction->getType()));
                        BB->getInstList().pop_back();
                        // LLVM is throwing an error if there is no name
                        // and you attempt to erase it
                        if (instruction->getName().size()) {
                            instruction->eraseFromParent();
                        }
                    }
                    
                    instruction = next;
                }
                
                break;
            }
        }
    }
  
    for (auto BBI = removedSuccessorsOf.begin(), BBE = removedSuccessorsOf.end(); BBI != BBE; ++BBI){
        CleanupBasicBlock(*BBI);
    }
    
    //Remove any dead blocks
    for (llvm::Function::iterator BB = function->begin(), e = function->end(); BB && BB != e; ++BB){
        if (BB->getName().startswith("entry")) {
            continue;
        }
        
        if (!BasicBlockGetNumPredecessors(BB)) {
            DeleteDeadBlock(BB);
        }
    }
}

void cujs::FunctionAddMissingTerminators(llvm::Function *function){
    for (llvm::Function::iterator BB = function->begin(), BBE = function->end(); BB != BBE; ++BB){
        if (!BB->getTerminator()){
            llvm::BasicBlock *jumpTarget = NULL;
         
            // Assume the user is jumping to the return if it is missing
            // this is looks naieve, but a correctly compiled program should not
            // violate this assumption
            for (llvm::Function::iterator BBJ = function->end(), BBJE = function->begin(); BBJ != BBJE; --BBJ){
                if (BBJ->getName().startswith(llvm::StringRef("return.set"))) {
                    jumpTarget = BBJ;
                    break;
                }
            }
            
            auto retJump = BranchInst::Create(jumpTarget);
            BB->getInstList().push_back(retJump);
        }
    }
}
