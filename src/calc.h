#ifndef _CALC_H_
#define _CALC_H_

#include "arena/arena.h"
#include "jit.h"

typedef struct calc_args_t {
    LLVMBuilderRef builder;
    LLVMValueRef value;
    arena_t *arena;
    double result;
    
} calc_args_t;

void yyerror (calc_args_t *, const char* s);

#endif /* _CALC_H_ */