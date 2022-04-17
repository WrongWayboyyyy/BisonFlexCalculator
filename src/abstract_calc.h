#ifndef _ABSTRACT_CALC_H_
#define _ABSTRACT_CALC_H_

typedef struct abstract_expr_calc_t 
{
  char* expr;
  void* extra;
  double (*calc) (struct abstract_expr_calc_t* );
  void (*destroy) (struct abstract_expr_calc_t* );
} abstract_expr_calc_t;

#endif /* _ABSTRACT_CALC_H_ */