#include "parser_calc.h"
#include "calc.lex.h"
#include "parser.tab.h"

YYSTYPE expr_parser_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  yyscan_t scanner;
  double result = 0;

  if (calc_lex_init_extra (&result, &scanner))
    {
      fprintf (stderr, "Failed to init scanner\n");
      exit (EXIT_FAILURE);
    }

  if (NULL == calc__scan_string (abstract_expr_calc->expr, scanner))
    {
      fprintf (stderr, "Failed to init lexer\n");
      exit (EXIT_FAILURE);
    }    

  if (parser_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      exit (EXIT_FAILURE);
    }

  return (result);
}

void expr_parser_destroy (abstract_expr_calc_t* abstract_expr_calc)
{
  return;
}

int expr_parser_init (abstract_expr_calc_t* abstract_expr_calc, char* expr)
{
  abstract_expr_calc->expr = expr;
  abstract_expr_calc->extra = NULL;
  abstract_expr_calc->calc = expr_parser_calc;
  abstract_expr_calc->destroy = expr_parser_destroy;
  return (EXIT_SUCCESS);
}

