#ifndef _ARENA_AST_H_
#define _ARENA_AST_H_
#include "carena.h"

extern int yylineno;

void yyerror (char* s);

typedef struct node {
    int nodetype;
    int l;  
    int r;
} node;

typedef struct value {
    int nodetype;
    double number;
} value;

struct node* newast (int nodetype, int l, int r);
struct node* newnum (double d);

double eval (struct node*);

void treefree (struct node*);

#endif /* _ARENA_AST_H_ */