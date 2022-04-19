#include <stdlib.h>

#include "ast_calc.h"
#include "ast.h"
#include "calc.lex.h"
#include "ast.tab.h"
#include "tree.h"

long double expr_ast_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  extra_t* extra = abstract_expr_calc->extra;

  return ast_eval(extra->arena);
}

void expr_ast_destroy (abstract_expr_calc_t* abstract_expr_calc)
{
  arena_t* arena = abstract_expr_calc->extra;
  arena_free (arena);
  return;
}

int expr_ast_init (abstract_expr_calc_t* abstract_expr_calc, char* expr)
{
  abstract_expr_calc->expr = expr;
  arena_t* arena = malloc (sizeof (arena_t));
  extra_t* extra = malloc (sizeof (extra_t));
  int rc = arena_construct (arena);
  if (rc)
    {
      fprintf(stderr, "Error while arena construction\n");
      return (EXIT_FAILURE);
    }

  extra->arena = arena;
  abstract_expr_calc->extra = extra;
  abstract_expr_calc->calc = expr_ast_calc;
  abstract_expr_calc->destroy = expr_ast_destroy;

  yyscan_t scanner;
  if (calc_lex_init_extra (extra, &scanner))
    {
      fprintf (stderr, "Failed to init scanner\n");
      exit (EXIT_FAILURE);
    }

  if (NULL == calc__scan_string (abstract_expr_calc->expr, scanner))
    {
      fprintf (stderr, "Failed to init lexer\n");
      exit (EXIT_FAILURE);
    }    

  if (ast_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      exit (EXIT_FAILURE);
    }

  return (EXIT_SUCCESS);
}

