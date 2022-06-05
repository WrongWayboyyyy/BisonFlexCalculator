#include <stdio.h>
#include <stdlib.h>

#include "llvm.h"

int llvm_init ( LLVMModuleRef* module, LLVMExecutionEngineRef* engine
              , LLVMBuilderRef* builder, LLVMValueRef* value )
{

  *module = LLVMModuleCreateWithName ("calc");

  LLVMTypeRef param_types[] = { LLVMDoubleType () };
  LLVMTypeRef ret_type = LLVMFunctionType ( LLVMDoubleType ()
                                          , param_types, 1, 0 );
  LLVMValueRef func = LLVMAddFunction (*module, "func", ret_type);

  LLVMBasicBlockRef entry = LLVMAppendBasicBlock (func, "entry");

  *builder = LLVMCreateBuilder ();
  *value = LLVMGetParam (func, 0);
  LLVMPositionBuilderAtEnd (*builder, entry);

  LLVMLinkInMCJIT ();
  LLVMInitializeNativeTarget ();
  LLVMInitializeNativeAsmPrinter ();

  char* error = NULL;
  if (LLVMCreateExecutionEngineForModule (&(*engine), *module, &error) != 0) 
    {
      fprintf (stderr, "Failed to create execution engine\n");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int llvm_verify (LLVMModuleRef* module, LLVMExecutionEngineRef* engine) 
{
  char* error = NULL;
  int rc = LLVMVerifyModule (*module, LLVMAbortProcessAction, &error);
  if (rc)
    {
      fprintf (stderr, "Failed to verify module: %s\n", error);
      LLVMDisposeMessage (error);
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}