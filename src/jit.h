#ifndef _AST_H_
#define _AST_H_

#include "llvm.h"

typedef struct extra_t 
{
  LLVMBuilderRef builder;
  LLVMExecutionEngineRef engine;
  double* result;
} extra_t;

typedef struct jit_value_t {
  LLVMValueRef rvalue;
  double val;
} jit_value_t;

#define JIT_STYPE jit_value_t
#define YYSTYPE JIT_STYPE

#endif /* _AST_H */