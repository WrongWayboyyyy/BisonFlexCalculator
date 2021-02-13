#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "structure.h"

struct Node* newast(int nodetype, struct Node* l, struct Node* r) {
    struct Node* a = malloc(sizeof(struct Node));

    if (!a) {
        yyerror("Not enough memory");
        exit(0);
    }

    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    
    return a;
}

struct Node* newnum(double d) {
    struct Value* a = malloc(sizeof(struct Value));
    if(!a) {
        yyerror("out of space");
        exit(0); 
    }
    a->nodetype = 'K';
    a->number = d;
    return (struct Node*) a;
}

double eval(struct Node* a) {
    double v;
    if (a->nodetype == 'K') {
        v = ((struct Value*)a)->number;
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
        v = eval(a->l);
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

void treefree(struct Node* a) {
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

int main(int argc, char** argv) {
    printf("> ");
    return yyparse();
}

void yyerror(char* s, ...) {
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}