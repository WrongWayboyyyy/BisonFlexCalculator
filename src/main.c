#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "abstract_calc.h"
#include "expr_calc.h"
#include "ast_calc.h"

typedef enum 
{
  CM_PARSE,
  CM_AST,
} calc_mode_t;

int main (int argc, char * argv[])
{
  abstract_expr_calc_t abstract_expr_calc;
  calc_mode_t calc_mode = CM_PARSE;
  int repeat = 1;
  int op;
  
  while ((op = getopt (argc, argv, "par:")) != -1)
    switch (op)
      {
      case 'p':
	      calc_mode = CM_PARSE;
	      break;
      case 'a':
	      calc_mode = CM_AST;
	      break;
      case 'r':
	      repeat = atoi (optarg);
	      break;
      }

  switch (calc_mode)
    {
    case CM_PARSE:
      expr_parse_init (&abstract_expr_calc, argv[optind]);
      break;
    case CM_AST:
      ast_parse_init (&abstract_expr_calc, argv[optind]);
      break;
    }
  
  int i;
  double sum = 0;
  for (i = 0; i < repeat; ++i)
    {
      double result = abstract_expr_calc.calc (&abstract_expr_calc);
      sum += result;
    }

  printf ("%s = %g\n", argv[optind], sum);

  abstract_expr_calc.destroy (&abstract_expr_calc);

  return (EXIT_SUCCESS);
}
