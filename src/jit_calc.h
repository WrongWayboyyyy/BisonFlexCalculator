#ifndef _JIT_CALC_H_
#define _JIT_CALC_H_

#include "abstract_calc.h"

double jit_parse_calc (abstract_expr_calc_t* abstract_expr_calc);

void jit_parse_destroy (abstract_expr_calc_t* abstract_expr_calc);

int jit_parse_init (abstract_expr_calc_t* abstract_expr_calc, char* expr);

#endif /* _JIT_CALC_H_ */