#include "arena/arena.h"
#include "jit.h"

typedef struct calc_args_t {
    LLVMBuilderRef builder;
    LLVMValueRef x;
    arena_t *arena;
    
} calc_args_t;

void yyerror (calc_args_t *, const char* s);