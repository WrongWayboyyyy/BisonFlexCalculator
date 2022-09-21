#include <stdlib.h>

#include "ast_calc.h"
#include "ast.h"
#include "calc.lex.h"
#include "ast.tab.h"
#include "tree.h"

int expr_ast_calc (abstract_expr_calc_t* calc)
{
  extra_t* extra = calc->extra;
  calc->result = ast_eval (extra->arena, extra->x_value);
  return (EXIT_SUCCESS);
}

void expr_ast_destroy (abstract_expr_calc_t* calc)
{
  arena_t* arena = calc->extra;
  arena_free (arena);
  free (calc->extra);

  return;
}

int expr_ast_init (abstract_expr_calc_t* calc, value_type_t x, char* expr)
{
  calc->expr = expr;
  extra_t* extra = malloc( sizeof (extra_t));
  extra->arena = malloc (sizeof (arena_t));
  int rc = arena_construct (extra->arena);
  if (rc)
    {
      fprintf(stderr, "Error while arena construction\n");
      return (EXIT_FAILURE);
    }
  calc->extra = extra;
  calc->calc = expr_ast_calc;
  calc->destroy = expr_ast_destroy;

  extra->x_value = x;
  yyscan_t scanner;
  if (calc_lex_init_extra (extra, &scanner))
    {
      fprintf (stderr, "Failed to init scanner\n");
      return (EXIT_FAILURE);
    }

  if (NULL == calc__scan_string (calc->expr, scanner))
    {
      fprintf (stderr, "Failed to init lexer\n");
      return (EXIT_FAILURE);
    }    

  if (ast_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      return (EXIT_FAILURE);
    }

  return (EXIT_SUCCESS);
}

