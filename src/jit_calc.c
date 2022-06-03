#include <stdlib.h>

#include "jit_calc.h"
#include "jit.h"
#include "calc.lex.h"
#include "jit.tab.h"

int expr_jit_calc (abstract_expr_calc_t* abstract_expr_calc)
{
  extra_t* extra = abstract_expr_calc->extra;
  LLVMExecutionEngineRef engine = extra->engine;
  
  VALUE_TYPE (*f)(VALUE_TYPE) = (VALUE_TYPE (*)(VALUE_TYPE)) 
      LLVMGetFunctionAddress (engine, "func");
  abstract_expr_calc->result = f(0.0);
  return (EXIT_SUCCESS);
}

void expr_jit_destroy (abstract_expr_calc_t* abstract_expr_calc)
{
  return;
}

int expr_jit_init (abstract_expr_calc_t* abstract_expr_calc, char* expr)
{
  abstract_expr_calc->expr = expr;
  extra_t* extra = malloc (sizeof (extra_t));
  if (!extra) 
    {
      fprintf (stderr, "Failed to allocate extra\n");
      return (EXIT_FAILURE);
    }
  LLVMModuleRef module;

  int rc = llvm_init (&module, &extra->engine, &extra->builder, &extra->value);

  if (rc)
    {
      return (EXIT_FAILURE);
    }


  abstract_expr_calc->extra = extra;
  abstract_expr_calc->calc = expr_jit_calc;
  abstract_expr_calc->destroy = expr_jit_destroy;

  yyscan_t scanner;

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

  if (jit_parse (scanner))
    {
      fprintf (stderr, "Failed to parse\n");
      return (EXIT_FAILURE);
    }

  rc = llvm_verify (&module, &extra->engine);

  if (rc)
    {
      return (EXIT_FAILURE);
    }

  return (EXIT_SUCCESS);
}

