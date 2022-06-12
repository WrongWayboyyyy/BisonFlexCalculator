#ifndef _PARSER_H_
#define _PARSER_H_

#include "value.h"

typedef struct parser_extra_t {
  value_type_t x_value;
  value_type_t result;
} extra_t;

#define PARSER_STYPE value_type_t
#define YYSTYPE PARSER_STYPE
#define parser_lex calc_lex

#endif /* _PARSER_H_ */
