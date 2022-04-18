#ifndef _AST_H_
#define _AST_H_


#include "tree.h"

typedef struct extra_t 
{
  arena_t* arena;
  double* result;
} extra_t;

#define AST_STYPE long double
#define YYSTYPE AST_STYPE

#endif /* _AST_H */