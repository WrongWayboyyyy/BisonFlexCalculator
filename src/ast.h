#ifndef _AST_H_
#define _AST_H_

#include <math.h>

#include "arena/node.h"
#include "arena/arena.h"
#include "calc.h"

typedef struct arena_t arena_t;
typedef struct node_t node_t;

unsigned int newnode ( calc_args_t *arena, int nodetype, 
                       unsigned int l, unsigned int r );
unsigned int newnum (calc_args_t *arena, double d);

double eval (calc_args_t *);

void treefree (node_t *);

#ifdef _AST_VERSION_

typedef double calc_type_t;

#define PARSE_TOKEN() {    \
    yylval = atof(yytext);  \
}

#define CALC_ADD(TOP, L, R) TOP = newnode (args, '+', L, R)
#define CALC_SUB(TOP, L, R) TOP = newnode (args, '-', L, R)
#define CALC_MUL(TOP, L, R) TOP = newnode (args, '*', L, R)
#define CALC_DIV(TOP, L, R) TOP = newnode (args, '/', L, R)
#define CALC_ABS(TOP, ARG) TOP = newnode (args, '|', ARG, -1)
#define CALC_NEG(TOP, ARG) TOP = newnode (args, 'M', ARG, -1)
#define CALC_NUM(TOP, ARG) TOP = newnum (args, ARG)
// TODO: Remove unused argument
#define CALC_RESULT(TOP) args->result = eval(args)

#endif /*_AST_VERSION_ */

#endif /* _AST_H_ */