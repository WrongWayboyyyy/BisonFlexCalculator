#ifndef _AST_H_
#define _AST_H_

extern int yylineno;

void yyerror (char* s);

typedef struct node {
    int nodetype;
    unsigned int l;
    unsigned int r;
} node;

typedef struct value {
    int nodetype;
    double number;
} value;

struct node* newast (int nodetype, unsigned int l, unsigned int r);
struct node* newnum (double d);

double eval (struct node*);

void treefree (struct node*);

#endif /* _AST_H_ */