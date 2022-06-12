#ifndef _TREE_H_
#define _TREE_H_

#include <math.h>

#include "arena.h"
#include "value.h"

typedef arena_t arena_t;

unsigned int ast_alloc_node ( arena_t* arena, int nodetype, 
                              unsigned int l, unsigned int r );
unsigned int ast_alloc_num (arena_t* arena, double d);

value_type_t ast_eval (arena_t*, value_type_t);

#endif /* _TREE_H_ */