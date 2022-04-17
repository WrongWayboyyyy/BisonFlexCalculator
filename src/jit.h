#ifndef _AST_H_
#define _AST_H_

#include "llvm.h"

typedef struct extra_t 
{
  LLVMBuilderRef builder;
  LLVMExecutionEngineRef engine;
  double* result;
} extra_t;

typedef struct calc_type_t {
  LLVMValueRef rvalue;
  double val;
} calc_type_t;

#define JIT_STYPE calc_type_t
#define YYSTYPE JIT_STYPE

#endif /* _AST_H */