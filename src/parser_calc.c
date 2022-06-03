#include <stdlib.h>

#include "parser_calc.h"
#include "calc.lex.h"
#include "parser.tab.h"

int expr_parser_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  yyscan_t scanner;

  if (calc_lex_init_extra (&abstract_expr_calc->result, &scanner))
    {
      fprintf (stderr, "Failed to init scanner\n");
      return (EXIT_FAILURE);
    }

  if (NULL == calc__scan_string (abstract_expr_calc->expr, scanner))
    {
      fprintf (stderr, "Failed to init lexer\n");
      return (EXIT_FAILURE);
    }    

  if (parser_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      return (EXIT_FAILURE);
    }


  return (EXIT_SUCCESS);
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

