#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "arena_ast.h"

unsigned int newast (arena* arena, int nodetype, unsigned int l, unsigned int r) {
    unsigned int n = arena_allocate(arena, 2);   
    if (n < 0) {
        yyerror(arena, "not enough memory");
        exit(0);
    }
    arena->arena[n].l = l;
    arena->arena[n].r = r;
    arena->arena[n].nodetype = nodetype;
    
    return n;
}

unsigned int newnum (arena* arena, double d) {
    unsigned int a = arena_allocate(arena, 2);
    if(a < 0) {
        yyerror(arena, "not enough memory");
        exit(0); 
    }
    value* val = (value*)(arena->arena + a);
    val->nodetype = 'K';
    val->number = d;
    return a;
}

double eval (arena* arena, struct node* a) {
    double v;
    if (a->nodetype == 'K') {
        struct value* val = (value*) a;
        v = val->number;
        //printf("I'm number %f! \n", v);
    } 
    else
    if (a->nodetype == '+') {
        //printf("I'm plus with %d %d! \n", a->l, a->r);
        v = eval(arena, &(arena->arena[a->l])) + eval(arena, &(arena->arena[a->r]));
    }
    else
    if (a->nodetype == '-') {
        v = eval(arena, &arena->arena[a->l]) - eval(arena, &arena->arena[a->r]);
    }
    else
    if (a->nodetype == '*') {
        v = eval(arena, &arena->arena[a->l]) * eval(arena, &arena->arena[a->r]);
    }
    else
    if (a->nodetype == '/') {
        v = eval(arena, &arena->arena[a->l]) / eval(arena, &arena->arena[a->r]);
    }
    else
    if (a->nodetype == '|') {
        v = abs(eval(arena, &arena->arena[a->l]));
    }
    else
    if (a->nodetype == 'M') {
        v = -eval(arena, &arena->arena[a->l]);
    }
    else {
        printf("internal error: bad node %c\n", a->nodetype);
    }
    return v;
}

void yyerror (arena* arg, char* s) {
    fprintf(stderr, "%d: error: ", yylineno);
    fprintf(stderr, "\n");
}