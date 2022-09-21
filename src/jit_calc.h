#ifndef _JIT_CALC_H_
#define _JIT_CALC_H_

#include "abstract_calc.h"

int expr_jit_calc (abstract_expr_calc_t* calc);

void expr_jit_destroy (abstract_expr_calc_t* calc);

int expr_jit_init (abstract_expr_calc_t* calc, value_type_t x_value, char* expr);

#endif /* _JIT_CALC_H_ */