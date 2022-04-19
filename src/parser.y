%code top {
#include "parser.h"
#include "calc.lex.h"
static void parser_error (void* scanner, char* error) {}
}

%param {void* scanner}
%define api.prefix {parser_}
%define api.pure full

%token NUMBER

%left '+' '-'
%left '*' '/'
%precedence UMINUS

%defines

%start result

%% 

result: expr 
{
  PARSER_STYPE* result = calc_get_extra (scanner);
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