#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "arena/arena.h"
#include "ast.h"
#include "calc.tab.h"

unsigned int newnode (arena_t* arena, int nodetype, unsigned int l, unsigned int r) {
    unsigned int n = arena_allocate (arena, 1);
    if (n < 0) {
        yyerror (arena, "Not enough memory");
        exit (0);
    }
    node_t* block = arena->arena + n;
    block->op.l = l;
    block->op.r = r;
    block->nodetype = nodetype;
    
    return n;
}

unsigned int newnum (arena_t* arena, double d) {
    unsigned int a = arena_allocate (arena, 1);
    if (a < 0) {
        yyerror (arena, "Not enough memory");
        exit (0); 
    }
    node_t* value = arena->arena + a;
    value->nodetype = 'K';
    value->val = d;
    return a;
}

double eval (arena_t* arena) {
    double results[arena->allocated];

    for (int i = 0; i < arena->allocated; ++i) {
        node_t* node = &arena->arena[i];
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

#ifdef _ARENA_VERSION_

#define CALC_ADD(TOP, L, R) TOP = newnode (arena, '+', L, R)
#define CALC_SUB(TOP, L, R) TOP = newnode (arena, '-', L, R)
#define CALC_MUL(TOP, L, R) TOP = newnode (arena, '*', L, R)
#define CALC_DIV(TOP, L, R) TOP = newnode (arena, '/', L, R)
#define CALC_ABS(TOP, ARG) TOP = newnode (arena, '|', ARG, -1)
#define CALC_NEG(TOP, ARG) TOP = newnode (arena, 'M', ARG, -1)
#define CALC_NUM(TOP, ARG) TOP = newnum (arena, ARG)
// TODO: Remove unused argument
#define CALC_RESULT(TOP) eval(arena) 
#endif /*_ARENA_VERSION_ */

#ifdef _NAIVE_VERSION_

#define CALC_ADD(TOP, L, R) TOP = L + R
#define CALC_SUB(TOP, L, R) TOP = L - R
#define CALC_MUL(TOP, L, R) TOP = L * R
#define CALC_DIV(TOP, L, R) TOP = L / R
#define CALC_ABS(TOP, ARG) TOP = fabs(ARG)
#define CALC_NEG(TOP, ARG) TOP = -ARG
#define CALC_NUM(TOP, ARG) TOP = ARG
#define CALC_RESULT(TOP) TOP

#endif /* _NAIVE_VERSION_ */
