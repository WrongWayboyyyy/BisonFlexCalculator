#ifndef _AST_H_
#define _AST_H_

#include <math.h>

#include "arena/node.h"
#include "arena/arena.h"

typedef struct arena_t arena_t;
typedef struct node_t node_t;

unsigned int newnode ( arena_t* arena, int nodetype, 
                       unsigned int l, unsigned int r );
unsigned int newnum (arena_t* arena, double d);

double eval (arena_t* arena);

void treefree (node_t*);

void yyerror (arena_t*, const char* s);

#ifdef _ARENA_VERSION_

#define CALC_MODE ARENA

#define CALC_ADD(TOP, L, R) TOP = newnode (arena, '+', L, R)
#define CALC_SUB(TOP, L, R) TOP = newnode (arena, '-', L, R)
#define CALC_MUL(TOP, L, R) TOP = newnode (arena, '*', L, R)
#define CALC_DIV(TOP, L, R) TOP = newnode (arena, '/', L, R)
#define CALC_ABS(TOP, ARG) TOP = newnode (arena, '|', ARG, -1)
#define CALC_NEG(TOP, ARG) TOP = newnode (arena, 'M', ARG, -1)
#define CALC_NUM(TOP, ARG) TOP = newnum (arena, ARG)
// TODO: Remove unused argument
#define CALC_RESULT(TOP) eval(arena) 
#endif /*_ARENA_VERSION_ */

#ifdef _NAIVE_VERSION_

#define CALC_ADD(TOP, L, R) TOP = L + R
#define CALC_SUB(TOP, L, R) TOP = L - R
#define CALC_MUL(TOP, L, R) TOP = L * R
#define CALC_DIV(TOP, L, R) TOP = L / R
#define CALC_ABS(TOP, ARG) TOP = fabs(ARG)
#define CALC_NEG(TOP, ARG) TOP = -ARG
#define CALC_NUM(TOP, ARG) TOP = ARG
#define CALC_RESULT(TOP) TOP

#endif /* _NAIVE_VERSION_ */

#endif /* _AST_H_ */