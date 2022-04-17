%code top {
  #include "expr.h"
  #include "expr.lex.h"
  static void expr_error (void* scanner, char* error) {}
}

%param {void* scanner}
%define api.prefix {expr_}
%define api.pure full

%token NUMBER

%left '+' '-'
%left '*' '/'
%precedence UMINUS

%defines

%start result

%% 

result: expr {
    EXPR_STYPE* result = expr_get_extra (scanner);
    *result = $1;
}

expr:
  expr '+' expr { $$ = $1 + $3; }
| expr '-' expr { $$ = $1 - $3; }
| expr '*' expr { $$ = $1 * $3; }
| expr '/' expr { $$ = $1 / $3; }
| '-' expr %prec UMINUS { $$ = -$2; }
| '+' expr %prec UMINUS { $$ = $2; }
| '(' expr ')' { $$ = $2; }
| NUMBER { $$ = $1; }


%%