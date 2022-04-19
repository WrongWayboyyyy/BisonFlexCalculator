#ifndef _LLVM_H_
#define _LLVM_H_

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

int llvm_init ( LLVMModuleRef* module, LLVMExecutionEngineRef* engine
               , LLVMBuilderRef* builder, LLVMValueRef* value );

int llvm_verify (LLVMModuleRef* module, LLVMExecutionEngineRef* engine);


#endif /* _LLVM_H_ */