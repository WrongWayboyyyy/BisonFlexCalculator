#include "ast_calc.h"
#include "tree/arena.h"

double ast_parse_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  yyscan_t scanner;
  double result = 0;

  if (ast_lex_init_extra (&result, &scanner))
    {
      fprintf (stderr, "Failed to init scanner\n");
      exit (EXIT_FAILURE);
    }

  if (NULL == ast__scan_string (abstract_expr_calc->expr, scanner))
    {
      fprintf (stderr, "Failed to init lexer\n");
      exit (EXIT_FAILURE);
    }    

  if (ast_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      exit (EXIT_FAILURE);
    }

  return (result);
}

void ast_parse_destroy (abstract_expr_calc_t* abstract_expr_calc)
{
  arena_t* arena = abstract_expr_calc->extra;
  arena_free (arena);
  return;
}

int expr_parse_init (abstract_expr_calc_t* abstract_expr_calc, char* expr)
{
  abstract_expr_calc->expr = expr;
  arena_t* arena = NULL;
  arena_construct(arena);
  abstract_expr_calc->extra = arena;
  abstract_expr_calc->calc = ast_parse_calc;
  abstract_expr_calc->destroy = ast_parse_destroy;
  return (EXIT_SUCCESS);
}

