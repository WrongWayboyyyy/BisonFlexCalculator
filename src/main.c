#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expr.h"
#include "expr.lex.h"
#include "expr.tab.h"

typedef struct abstract_expr_calc_t {
  char* expr;
  void* extra;
  EXPR_STYPE (*calc) (struct abstract_expr_calc_t* );
  void (*destroy) (struct abstract_expr_calc_t* );
} abstract_expr_calc_t;

EXPR_STYPE expr_parse_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  yyscan_t scanner;
  EXPR_STYPE result = 0;

  if (expr_lex_init_extra (&result, &scanner))
    {
      fprintf (stderr, "Failed to init scanner\n");
      return (EXIT_FAILURE);
    }

  if (NULL == expr__scan_string (abstract_expr_calc->expr, scanner))
    {
      fprintf (stderr, "Failed to init lexer\n");
      return (EXIT_FAILURE);
    }    

  if (expr_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      return (EXIT_FAILURE);
    }

  return (result);
}

void expr_parse_destroy (abstract_expr_calc_t* abstract_expr_calc)
{
  return;
}

int expr_parse_init (abstract_expr_calc_t* abstract_expr_calc, char* expr)
{
  abstract_expr_calc->expr = expr;
  abstract_expr_calc->extra = NULL;
  abstract_expr_calc->calc = expr_parse_calc;
  abstract_expr_calc->destroy = expr_parse_destroy;
  return (EXIT_SUCCESS);
}

typedef enum {
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
      expr_parse_init (&abstract_expr_calc, argv[optind]);
      break;
    }
  
  int i;
  EXPR_STYPE sum = 0;
  for (i = 0; i < repeat; ++i)
    {
      EXPR_STYPE result = abstract_expr_calc.calc (&abstract_expr_calc);
      sum += result;
    }

  printf ("%s = %g\n", argv[optind], sum);

  abstract_expr_calc.destroy (&abstract_expr_calc);

  return (EXIT_SUCCESS);
}
