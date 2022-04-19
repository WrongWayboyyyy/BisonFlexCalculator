#ifndef _PARSER_CALC_H_
#define _PARSER_CALC_H_

#include "parser.h"
#include "abstract_calc.h"

int expr_parser_calc (abstract_expr_calc_t* abstract_expr_calc);

void expr_parser_destroy (abstract_expr_calc_t* abstract_expr_calc);

int expr_parser_init (abstract_expr_calc_t* abstract_expr_calc, char* expr);

#endif /* _PARSER_CALC_H_ */