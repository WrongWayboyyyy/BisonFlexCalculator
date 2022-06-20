#include <stdlib.h>

#include "jit_calc.h"
#include "jit.h"
#include "calc.lex.h"
#include "jit.tab.h"

int expr_jit_calc (abstract_expr_calc_t* calc)
{
  extra_t* extra = calc->extra;
  calc->result = extra->f (extra->x_value);
  return (EXIT_SUCCESS);
}

void expr_jit_destroy (abstract_expr_calc_t* calc)
{
  extra_t* extra = calc->extra;
  llvm_destroy (&extra->module, &extra->builder); 
  free (calc->extra);
  return;
}

int expr_jit_init (abstract_expr_calc_t* calc, value_type_t x, char* expr)
{
  calc->expr = expr;
  extra_t* extra = malloc (sizeof (extra_t));
  extra->x_value = x;
  if (!extra) 
    {
      fprintf (stderr, "Failed to allocate extra\n");
      return (EXIT_FAILURE);
    }

  int rc = llvm_init ( &extra->module, &extra->engine
                     , &extra->builder, &extra->value );

  if (rc)
    {
      return (EXIT_FAILURE);
    }

  calc->extra = extra;
  calc->calc = expr_jit_calc;
  calc->destroy = expr_jit_destroy;

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

  if (jit_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      return (EXIT_FAILURE);
    }

  rc = llvm_verify (&extra->module, &extra->engine);  

  if (rc)
    {
      return (EXIT_FAILURE);
    }

  extra->f = (value_type_t (*)(value_type_t)) 
      LLVMGetFunctionAddress (extra->engine, "func");

  return (EXIT_SUCCESS);
}

