#ifndef _EXPR_CALC_H_
#define _EXPR_CALC_H_

#include "expr.h"
#include "expr.lex.h"
#include "expr.tab.h"
#include "abstract_calc.h"

EXPR_STYPE expr_parse_calc (abstract_expr_calc_t* abstract_expr_calc);

void expr_parse_destroy (abstract_expr_calc_t* abstract_expr_calc);

int expr_parse_init (abstract_expr_calc_t* abstract_expr_calc, char* expr);

#endif /* _EXPR_CALC_H_ */