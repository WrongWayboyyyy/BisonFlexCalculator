#ifndef _TREE_H_
#define _TREE_H_

typedef struct arena_t arena_t;
typedef struct node_t node_t;

unsigned int newnode ( node_t* arena, int nodetype, 
                       unsigned int l, unsigned int r );
unsigned int newnum (node_t* arena, double d);

double eval (node_t* );

void treefree (node_t* );

// #define CALC_ADD(TOP, L, R) TOP = newnode (args, '+', L, R)
// #define CALC_SUB(TOP, L, R) TOP = newnode (args, '-', L, R)
// #define CALC_MUL(TOP, L, R) TOP = newnode (args, '*', L, R)
// #define CALC_DIV(TOP, L, R) TOP = newnode (args, '/', L, R)
// #define CALC_ABS(TOP, ARG) TOP = newnode (args, '|', ARG, -1)
// #define CALC_NEG(TOP, ARG) TOP = newnode (args, 'M', ARG, -1)
// #define CALC_NUM(TOP, ARG) TOP = newnum (args, ARG)
// // TODO: Remove unused argument
// #define CALC_RESULT(TOP) args->result = eval(args)

#endif /* _TREE_H_ */