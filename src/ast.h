#ifndef _AST_H_
#define _AST_H_

#include "tree.h"
#include "value.h"

typedef struct ast_extra_t {
  arena_t* arena;
  value_type_t x_value;
} extra_t;

#define AST_STYPE value_type_t
#define YYSTYPE AST_STYPE
#define ast_lex calc_lex

#endif /* _AST_H_ */