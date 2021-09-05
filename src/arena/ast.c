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
    block->op.l = l;
    block->op.r = r;
    block->nodetype = nodetype;
    
    return n;
}

unsigned int newnum (arena* arena, double d) {
    unsigned int a = arena_allocate(arena, 1);
    if (a < 0) {
        yyerror(arena, "Not enough memory");
        exit(0); 
    }
    node* value = arena->arena + a;
    value->nodetype = 'K';
    value->val = d;
    return a;
}

double eval (arena* arena) {
    double results[arena->allocated];

    for (int i = 0; i < arena->allocated; ++i) {
        node* node = &arena->arena[i];
        switch (node->nodetype) {
            case 'K' : {
                results[i] = node->val;
                break;
            }
            case '+' : {
                results[i] = results[node->op.l] + results[node->op.r];
                break;
            }
            case '-' :
                results[i] = results[node->op.l] - results[node->op.r];
                break;
            case '*' :
                results[i] = results[node->op.l] * results[node->op.r];
                break;
            case '/' :
                results[i] = results[node->op.l] / results[node->op.r];
                break;
            case '|' :
                results[i] = fabs(results[node->op.l]);
                break;
            case 'M' :
                results[i] = -results[node->op.l];
                break;
            default:
                printf("Internal error: bad node %c\n", node->nodetype);
                break;
        }
    }
    return results[arena->allocated - 1];
}
