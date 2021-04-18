#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "arena_ast.h"

struct node* newast(int nodetype, int l, int r) {
    struct node* a = malloc(sizeof(struct node));

    if (!a) {
        yyerror("Not enough memory");
        exit(0);
    }

    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    
    return a;
}

struct node* newnum(double d) {
    struct value* a = malloc(sizeof(struct value));
    if(!a) {
        yyerror("out of space");
        exit(0); 
    }
    a->nodetype = 'K';
    a->number = d;
    return (struct node*) a;
}

double eval(struct node* a) {
    double v;
    if (a->nodetype == 'K') {
        v = ((struct value*)a)->number;
    } 
    else
    if (a->nodetype == '+') {
        v = eval(a->l) + eval(a->r);
    }
    else
    if (a->nodetype == '-') {
        v = eval(a->l) - eval(a->r);
    }
    else
    if (a->nodetype == '*') {
        v = eval(a->l) * eval(a->r);
    }
    else
    if (a->nodetype == '/') {
        v = eval(a->l) / eval(a->r);
    }
    else
    if (a->nodetype == '|') {
        v = abs(eval(a->l));
    }
    else
    if (a->nodetype == 'M') {
        v = -eval(a->l);
    }
    else {
        printf("internal error: bad node %c\n", a->nodetype);
    }
    return v;
}

void treefree(struct node* a) {
    if (a->nodetype == '+' || a->nodetype == '-' || a->nodetype == '*' || a->nodetype == '/') {
        treefree(a->r);
        treefree(a->l);
        free(a);
    }
    else
    if (a->nodetype == '|' || a->nodetype == 'M') {
        treefree(a->l);
        free(a);
    }
    else
    if (a->nodetype == 'K') {
        free(a);
    }
    else {
        printf("internal error: free bad node %c\n", a->nodetype);
    } 
}