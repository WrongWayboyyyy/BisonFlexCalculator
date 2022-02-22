#ifndef _AST_H_
#define _AST_H_
#include "node.h"
#include "arena.h"

#define YYSTYPE double
#define CALC_MODE ARENA

typedef struct arena_t arena_t;
typedef struct node_t node_t;

unsigned int newnode ( arena_t* arena, int nodetype, 
                       unsigned int l, unsigned int r );
unsigned int newnum (arena_t* arena, double d);

double eval (arena_t* arena);

void treefree (node_t*);

void yyerror (arena_t*, const char* s);

#define CALC_ADD(TOP, L, R) TOP = newnode (arena, '+', L, R)
#define CALC_SUB(TOP, L, R) TOP = newnode (arena, '-', L, R)
#define CALC_MUL(TOP, L, R) TOP = newnode (arena, '*', L, R)
#define CALC_DIV(TOP, L, R) TOP = newnode (arena, '/', L, R)
#define CALC_ABS(TOP, ARG) TOP = newnode (arena, '|', ARG, -1)
#define CALC_NEG(TOP, ARG) TOP = newnode (arena, 'M', ARG, -1)
#define CALC_NUM(TOP, ARG) TOP = newnum (arena, ARG)
// TODO: Remove unused argument
#define CALC_RESULT(TOP) eval(arena) 


#endif /* _AST_H_ */