#ifndef _JIT_H_
#define _JIT_H_

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>


#ifdef _JIT_VERSION_

typedef union calc_type_t {
    long double val;
    LLVMValueRef rvalue;
} calc_type_t;

#define PARSE_TOKEN() yylval.val = atof(yytext)

#define CALC_ADD(TOP, L, R) TOP.rvalue = LLVMBuildAdd(args->builder, L.rvalue, R.rvalue, "add"); 

#define CALC_SUB(TOP, L, R) TOP
#define CALC_MUL(TOP, L, R) TOP
#define CALC_DIV(TOP, L, R) TOP
#define CALC_ABS(TOP, ARG) TOP
#define CALC_NEG(TOP, ARG) TOP
#define CALC_NUM(TOP, ARG) TOP.rvalue = LLVMConstInt(LLVMInt32Type(), ARG.val, 1);  

#define CALC_RESULT(TOP) {                                        \
    LLVMBuildRet(args->builder, TOP.rvalue);                      \
} 

#endif

#endif /* _JIT_H_ */