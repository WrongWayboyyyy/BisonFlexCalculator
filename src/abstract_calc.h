#ifndef _ABSTRACT_CALC_H_
#define _ABSTRACT_CALC_H_

#include "value.h"

typedef struct abstract_expr_calc_t 
{
  char* expr;
  void* extra;
  int (*calc) (struct abstract_expr_calc_t* );
  void (*destroy) (struct abstract_expr_calc_t* );
  value_type_t result;
} abstract_expr_calc_t;

#endif /* _ABSTRACT_CALC_H_ */