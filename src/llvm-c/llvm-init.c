#include <stdio.h>
#include <stdlib.h>

#include "llvm-init.h"

void llvm_init ( LLVMModuleRef* module, LLVMExecutionEngineRef* engine
               , LLVMBuilderRef* builder, LLVMValueRef* value ) {

    *module = LLVMModuleCreateWithName ("calc");

    LLVMTypeRef param_types[] = { LLVMDoubleType () };
    LLVMTypeRef ret_type = LLVMFunctionType (LLVMDoubleType ()
                                            , param_types, 1, 0);
    LLVMValueRef func = LLVMAddFunction (*module, "func", ret_type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock (func, "entry");

    *builder = LLVMCreateBuilder ();
    *value = LLVMGetParam (func, 0);
    LLVMPositionBuilderAtEnd (*builder, entry);

    LLVMLinkInMCJIT ();
    LLVMInitializeNativeTarget ();
    LLVMInitializeNativeAsmPrinter ();

    char *error = NULL;
    if (LLVMCreateExecutionEngineForModule (&(*engine), *module, &error) != 0) {
        fprintf (stderr, "failed to create execution engine\n");
        abort ();
    }

}

void llvm_verify (LLVMModuleRef* module, LLVMExecutionEngineRef* engine) {
    char *error = NULL;
    LLVMVerifyModule (*module, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage (error);

    if (error) {
        fprintf (stderr, "error: %s\n", error);
        LLVMDisposeMessage (error);
        exit (EXIT_FAILURE);
    }
}