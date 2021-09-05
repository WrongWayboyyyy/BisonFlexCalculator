#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ast.h"
#include <math.h>

unsigned int newnode (arena* arena, int nodetype, unsigned int l, unsigned int r) {
    unsigned int n = arena_allocate(arena, 1);
    if (n < 0) {
        yyerror(arena, "Not enough memory");
        exit(0);
    }
    node* block = arena->arena + n;
    block->l = l;
    block->r = r;
    block->nodetype = nodetype;
    
    return n;
}

unsigned int newnum (arena* arena, double d) {
    unsigned int a = arena_allocate(arena, 2);
    if (a < 0) {
        yyerror(arena, "Not enough memory");
        exit(0); 
    }
    value* val = (value*)(arena->arena + a);
    val->nodetype = 'K';
    val->number = d;
    return a;
}

double eval (arena* arena) {
    double result = 0;
    double first_arg = 0;
    double second_arg = 0;
    node* block = arena->arena;
    int index = 0;
    while (index < arena->allocated) {
        node* node = block + index;
        unsigned int type = node->nodetype;
        switch (type) {
            case 'K' : {
                value* val = (value*) node;
                first_arg = second_arg;
                second_arg = val->number;
                index += 2;
                break;
            }
            case '+': {
                second_arg += first_arg;
                index += 1;
                break;
            }
            case '-': {
                first_arg -= second_arg;
                double tmp = first_arg;
                first_arg = second_arg;
                second_arg = tmp;
                index += 1;
                break;
            }
        }
        printf("%f, %f \n", first_arg, second_arg);
    }
    printf("\n");
    return second_arg;
}
