#ifndef _JIT_H_
#define _JIT_H_

#include "llvm.h"

typedef struct extra_t 
{
  LLVMBuilderRef builder;
  LLVMExecutionEngineRef engine;
  double* result;
} extra_t;

typedef union jit_value_t {
  LLVMValueRef rvalue;
  double val;
} jit_value_t;

#define JIT_STYPE jit_value_t
#define YYSTYPE JIT_STYPE
#define jit_lex calc_lex

#endif /* _JIT_H */