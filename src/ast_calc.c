#include <stdlib.h>

#include "ast_calc.h"
#include "ast.h"
#include "ast.lex.h"
#include "ast.tab.h"

double ast_parse_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  yyscan_t scanner;
  extra_t* extra = abstract_expr_calc->extra;
  double result = 0;
  extra->result = &result;

  if (ast_lex_init_extra (extra, &scanner))
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

  return result;
}

void ast_parse_destroy (abstract_expr_calc_t* abstract_expr_calc)
{
  arena_t* arena = abstract_expr_calc->extra;
  arena_free (arena);
  return;
}

int ast_parse_init (abstract_expr_calc_t* abstract_expr_calc, char* expr)
{
  abstract_expr_calc->expr = expr;
  arena_t* arena = malloc (sizeof (arena_t));
  extra_t* extra = malloc (sizeof (extra_t));
  int rc = arena_construct (arena);
  if (rc)
    {
      printf("Error while arena construction\n");
      return (EXIT_FAILURE);
    }

  extra->arena = arena;
  abstract_expr_calc->extra = extra;
  abstract_expr_calc->calc = ast_parse_calc;
  abstract_expr_calc->destroy = ast_parse_destroy;
  return (EXIT_SUCCESS);
}

