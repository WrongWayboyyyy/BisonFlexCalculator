#ifndef _TREE_H_
#define _TREE_H_

#include "arena.h"
#include <math.h>

typedef arena_t arena_t;

unsigned int ast_alloc_node ( arena_t* arena, int nodetype, 
                       unsigned int l, unsigned int r );
unsigned int ast_alloc_num (arena_t* arena, double d);

double ast_eval (arena_t* );

#endif /* _TREE_H_ */