//
//  cujsllvmutils.h
//  cujs
//
//  Created by Jerry Marino on 8/28/14.
//  Copyright (c) 2014 Jerry Marino. All rights reserved.
//

#ifndef __cujs__cujsllvmutils__
#define __cujs__cujsllvmutils__

#include <iostream>

namespace cujs {
    unsigned BasicBlockGetNumPredecessors(llvm::BasicBlock *BB);
    
    // FunctionCleanupInstructionsAfterTerminator - safely attempt to cleanup a
    // "poorly" formed function with instructions after any given terminator ;)
    void FunctionCleanupInstructionsAfterTerminator(llvm::Function *function);
    
    // FunctionAddMissingTerminators - add missing terminators to all the basic blocks
    // in this function - terminators jump to the return
    void FunctionAddMissingTerminators(llvm::Function *function);
}

#endif /* defined(__cujs__cujsllvmutils__) */
