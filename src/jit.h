#ifndef _JIT_H_
#define _JIT_H_

#include "llvm.h"
#include "value.h"

typedef struct extra_t 
{
  LLVMBuilderRef builder;
  LLVMExecutionEngineRef engine;
  LLVMModuleRef module;
  LLVMValueRef value;
  value_type_t x_value;
  
} extra_t;

typedef union jit_value_t {
  LLVMValueRef rvalue;
  value_type_t val;
} jit_value_t;

#define JIT_STYPE jit_value_t
#define YYSTYPE JIT_STYPE
#define jit_lex calc_lex

#endif /* _JIT_H_ */