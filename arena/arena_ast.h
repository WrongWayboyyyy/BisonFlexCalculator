#ifndef _AST_H_
#define _AST_H_
#include "arena.h"

extern int yylineno;

typedef struct node {
    int nodetype;
    unsigned int l;
    unsigned int r;
} node;

typedef struct value {
    int nodetype;
    double number;
} value;

unsigned int newast (struct arena* arena, int nodetype, 
    unsigned int l, unsigned int r);
unsigned int newnum (struct arena*, double d);

double eval (struct arena* arena, struct node* node);

void treefree (struct node*);


void yyerror(struct arena* arg, char* s);

#endif /* _AST_H_ */