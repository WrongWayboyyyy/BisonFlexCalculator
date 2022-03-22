#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "arena/arena.h"
#include "ast.h"
#include "calc.tab.h"

unsigned int newnode (calc_args_t* args, int nodetype, unsigned int l, unsigned int r) {
    arena_t* arena = args->arena;
    unsigned int n = arena_allocate (arena, 1);
    if (n < 0) {
        yyerror (args, "Not enough memory");
        exit (0);
    }
    node_t* block = arena->arena + n;
    block->op.l = l;
    block->op.r = r;
    block->nodetype = nodetype;
    
    return n;
}

unsigned int newnum (calc_args_t* args, double d) {
    arena_t* arena = args->arena;
    unsigned int a = arena_allocate (arena, 1);
    if (a < 0) {
        yyerror (args, "Not enough memory");
        exit (0); 
    }
    node_t *value = arena->arena + a;
    value->nodetype = 'K';
    value->val = d;
    return a;
}

double eval (calc_args_t* args) {
    arena_t* arena = args->arena;
    double results[arena->allocated];

    for (int i = 0; i < arena->allocated; ++i) {
        node_t *node = &arena->arena[i];
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
                results[i] = fabs (results[node->op.l]);
                break;
            case 'M' :
                results[i] = -results[node->op.l];
                break;
            default:
                printf ("Internal error: bad node %c\n", node->nodetype);
                break;
        }
    }
    return results[arena->allocated - 1];
}