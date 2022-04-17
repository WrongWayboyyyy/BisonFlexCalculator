#include "expr_calc.h"
#include "expr.lex.h"
#include "expr.tab.h"

double expr_parse_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  yyscan_t scanner;
  double result = 0;

  if (expr_lex_init_extra (&result, &scanner))
    {
      fprintf (stderr, "Failed to init scanner\n");
      exit (EXIT_FAILURE);
    }

  if (NULL == expr__scan_string (abstract_expr_calc->expr, scanner))
    {
      fprintf (stderr, "Failed to init lexer\n");
      exit (EXIT_FAILURE);
    }    

  if (expr_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      exit (EXIT_FAILURE);
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

