#ifndef _AST_H_
#define _AST_H_
#include "node.h"
#include "arena.h"

#define YYSTYPE unsigned int
#define CALC_MODE ARENA

extern int yylineno;

typedef struct arena arena;
typedef struct node node;

unsigned int newnode (arena* arena, int nodetype, 
    unsigned int l, unsigned int r);
unsigned int newnum (arena* arena, double d);

double eval (arena* arena);

void treefree (node*);

void yyerror (arena*, const char* s);

#define CALC_ADD(TOP, L, R) TOP = newnode(arena, '+', L, R)
#define CALC_SUB(TOP, L, R) TOP = newnode(arena, '-', L, R)
#define CALC_MUL(TOP, L, R) TOP = newnode(arena, '*', L, R)
#define CALC_DIV(TOP, L, R) TOP = newnode(arena, '/', L, R)
#define CALC_ABS(TOP, ARG) TOP = newnode(arena, '|', ARG, -1)
#define CALC_NEG(TOP, ARG) TOP = newnode(arena, 'M', ARG, -1)
#define CALC_NUM(TOP, ARG) TOP = newnum(arena, ARG)
#define CALC_RESULT(TOP) eval(arena)


#endif /* _AST_H_ */