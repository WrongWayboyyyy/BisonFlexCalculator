#ifndef _AST_H_
#define _AST_H_

#include "tree.h"

typedef struct arena_t extra_t;

#define AST_STYPE long double
#define YYSTYPE AST_STYPE
#define ast_lex calc_lex

#endif /* _AST_H */