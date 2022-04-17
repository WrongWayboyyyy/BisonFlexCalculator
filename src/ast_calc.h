#ifndef _AST_CALC_H_
#define _AST_CALC_H_

#include "tree.h"

typedef struct extra_t {
  arena_t* arena;
  double* result;
} extra_t;

#include "abstract_calc.h"

double ast_parse_calc (abstract_expr_calc_t* abstract_expr_calc);

void ast_parse_destroy (abstract_expr_calc_t* abstract_expr_calc);

int ast_parse_init (abstract_expr_calc_t* abstract_expr_calc, char* expr);

#endif /* _AST_CALC_H_ */