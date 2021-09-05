#ifndef _AST_H_
#define _AST_H_

#define YYSTYPE double

extern int yylineno;

#define CALC_ADD(TOP, L, R) TOP = L + R
#define CALC_SUB(TOP, L, R) TOP = L - R
#define CALC_MUL(TOP, L, R) TOP = L * R
#define CALC_DIV(TOP, L, R) TOP = L / R
#define CALC_ABS(TOP, ARG) TOP = fabs(ARG)
#define CALC_NEG(TOP, ARG) TOP = -ARG
#define CALC_NUM(TOP, ARG) TOP = ARG
#define CALC_RESULT(TOP) TOP

#endif /* _AST_H_ */