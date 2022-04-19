#ifndef _AST_CALC_H_
#define _AST_CALC_H_

#include "abstract_calc.h"

int expr_ast_calc (abstract_expr_calc_t* abstract_expr_calc);

void expr_ast_destroy (abstract_expr_calc_t* abstract_expr_calc);

int expr_ast_init (abstract_expr_calc_t* abstract_expr_calc, char* expr);

#endif /* _AST_CALC_H_ */