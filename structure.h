#ifndef _STRUCT_H_
#define _STRUCT_H_

extern int yylineno;

void yyerror(char* s);

typedef struct node {
    int nodetype;
    struct node* l;
    struct node* r;
} node;

typedef struct value {
    int nodetype;
    double number;
} value;

struct node* newast(int nodetype, struct node* l, struct node* r);
struct node* newnum(double d);

double eval(struct node*);

void treefree(struct node*);

#endif