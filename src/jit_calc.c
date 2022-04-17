#include <stdlib.h>

#include "jit_calc.h"
#include "jit.h"
#include "jit.lex.h"
#include "jit.tab.h"

long double expr_jit_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  yyscan_t scanner;
  extra_t* extra = abstract_expr_calc->extra;
  double result = 0;
  extra->result = &result;

  if (jit_lex_init_extra (extra, &scanner))
    {
      fprintf (stderr, "Failed to init scanner\n");
      exit (EXIT_FAILURE);
    }
  // fprintf(stderr, "%s", abstract_expr_calc->expr);
  if (NULL == jit__scan_string (abstract_expr_calc->expr, scanner))
    {
      fprintf (stderr, "Failed to init lexer\n");
      exit (EXIT_FAILURE);
    }    

  if (jit_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      exit (EXIT_FAILURE);
    }

  return result;
}

void expr_jit_destroy (abstract_expr_calc_t* abstract_expr_calc)
{
  return;
}

int expr_jit_init (abstract_expr_calc_t* abstract_expr_calc, char* expr)
{
  abstract_expr_calc->expr = expr;
  extra_t* extra = malloc (sizeof (extra_t));
  LLVMModuleRef module;
  LLVMExecutionEngineRef engine;
  LLVMBuilderRef builder;
  LLVMValueRef value;

  llvm_init (&module, &engine, &builder, &value);
  extra->builder = builder;
  extra->engine = engine;
  abstract_expr_calc->extra = extra;
  abstract_expr_calc->calc = expr_jit_calc;
  abstract_expr_calc->destroy = expr_jit_destroy;
  return (EXIT_SUCCESS);
}

