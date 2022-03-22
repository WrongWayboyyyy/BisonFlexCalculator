#include <stdio.h>
#include <stdlib.h>

#include "funcs.h"
#include "llvm-init.h"


void llvm_init (LLVMModuleRef* mod, LLVMExecutionEngineRef* engine) {

    *mod = LLVMModuleCreateWithName ("calc");

    LLVMTypeRef param_types[] = { LLVMInt32Type (), LLVMInt32Type () };
    LLVMTypeRef ret_type = LLVMFunctionType (LLVMInt32Type ()
                                            , param_types, 2, 0);
    LLVMValueRef sum = LLVMAddFunction (*mod, "sum", ret_type);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock (sum, "entry");

    LLVMBuilderRef builder = LLVMCreateBuilder ();
    LLVMPositionBuilderAtEnd (builder, entry);

    LLVMValueRef tmp = LLVMBuildAdd (builder, LLVMGetParam (sum, 0)
                                            , LLVMGetParam (sum, 1)
                                            , "tmp");
    LLVMBuildRet (builder, tmp);

    char *error = NULL;
    LLVMVerifyModule (*mod, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage (error);

    error = NULL;
    LLVMLinkInMCJIT ();
    LLVMInitializeNativeTarget ();
    LLVMInitializeNativeAsmPrinter ();
    if (LLVMCreateExecutionEngineForModule (&(*engine), *mod, &error) != 0) {
        fprintf (stderr, "failed to create execution engine\n");
        abort ();
    }
    if (error) {
        fprintf (stderr, "error: %s\n", error);
        LLVMDisposeMessage (error);
        exit (EXIT_FAILURE);
    }

}