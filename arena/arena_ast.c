#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "arena_ast.h"
#include "carena.h"

void yyerror(arena* arg, char* s);

unsigned int newast(arena* arena, int nodetype, unsigned int l, unsigned int r) {
    unsigned int n = arena_allocate(arena, 1);   
    if (n < 0) {
        yyerror(arena, "not enough memory");
        exit(0);
    }
    arena->arena[n].l = l;
    arena->arena[n].r = r;
    arena->arena[n].nodetype = nodetype;
    
    return n;
}

unsigned int newnum(arena* arena, double d) {
    unsigned int a = arena_allocate(arena, 1);
    if(!a) {
        yyerror(arena, "not enough memory");
        exit(0); 
    }
    value* val = (arena->arena + a);
    val->nodetype = 'K';
    val->number = d;
    return a;
}

double eval(arena* arena, struct node* a) {
    double v;
    if (a->nodetype == 'K') {
        v = ((struct value*)a)->number;
    } 
    else
    if (a->nodetype == '+') {
        v = eval(arena, &arena->arena[a->l]) + 
            eval(arena, &arena->arena[a->r]);
    }
    else
    if (a->nodetype == '-') {
        v = eval(arena, &arena->arena[a->l]) - 
            eval(arena, &arena->arena[a->r]);
    }
    else
    if (a->nodetype == '*') {
        v = eval(arena, &arena->arena[a->l]) * 
            eval(arena, &arena->arena[a->r]);
    }
    else
    if (a->nodetype == '/') {
        v = eval(arena, &arena->arena[a->l]) / 
            eval(arena, &arena->arena[a->r]);
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
    return 0;
}

void treefree(struct node* a) {
    // if (a->nodetype == '+' || a->nodetype == '-' || a->nodetype == '*' || a->nodetype == '/') {
    //     treefree(a->r);
    //     treefree(a->l);
    //     free(a);
    // }
    // else
    // if (a->nodetype == '|' || a->nodetype == 'M') {
    //     treefree(a->l);
    //     free(a);
    // }
    // else
    // if (a->nodetype == 'K') {
    //     free(a);
    // }
    // else {
    //     printf("internal error: free bad node %c\n", a->nodetype);
    // } 

}

void yyerror(arena* arg, char* s) {
    fprintf(stderr, "%d: error: ", yylineno);
    fprintf(stderr, "\n");
}