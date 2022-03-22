#ifndef _LLVM_INIT_H_
#define _LLVM_INIT_H_

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

void llvm_init ( LLVMModuleRef* module, LLVMExecutionEngineRef* engine
               , LLVMBuilderRef* builder, LLVMValueRef* value );

void llvm_verify (LLVMModuleRef* module, LLVMExecutionEngineRef* engine);


#endif /* _LLVM_INIT_H_ */

