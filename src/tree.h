#ifndef _TREE_H_
#define _TREE_H_

#include "arena.h"
#include <math.h>

unsigned int newnode ( arena_t* arena, int nodetype, 
                       unsigned int l, unsigned int r );
unsigned int newnum (arena_t* arena, double d);

double eval (arena_t* );

void treefree (arena_t* );

// #define CALC_ADD(TOP, L, R) TOP = newnode (args, '+', L, R)
// #define CALC_SUB(TOP, L, R) TOP = newnode (args, '-', L, R)
// #define CALC_MUL(TOP, L, R) TOP = newnode (args, '*', L, R)
// #define CALC_DIV(TOP, L, R) TOP = newnode (args, '/', L, R)
// #define CALC_ABS(TOP, ARG) TOP = newnode (args, '|', ARG, -1)
// #define CALC_NEG(TOP, ARG) TOP = newnode (args, 'M', ARG, -1)
// #define CALC_NUM(TOP, ARG) TOP = newnum (args, ARG)
// // TODO: Remove unused argument
// #define CALC_RESULT(TOP) args->result = eval(args)

#endif /* _TREE_H_ */