#include <stdlib.h>

#include "parser_calc.h"
#include "calc.lex.h"
#include "parser.tab.h"

int expr_parser_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  yyscan_t scanner;

  extra_t* extra = abstract_expr_calc->extra;

  if (calc_lex_init_extra (extra, &scanner))
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

  abstract_expr_calc->result = extra->result;

  return (EXIT_SUCCESS);
}

void expr_parser_destroy (abstract_expr_calc_t* calc)
{
  // free(abstract_expr_calc->extra);
  return;
}

int expr_parser_init (abstract_expr_calc_t* calc, value_type_t x, char* expr)
{
  calc->expr = expr;
  extra_t* extra = malloc (sizeof (extra_t));
  extra->x_value = x;
  calc->extra = extra;
  calc->calc = expr_parser_calc;
  calc->destroy = expr_parser_destroy;
  return (EXIT_SUCCESS);
}

