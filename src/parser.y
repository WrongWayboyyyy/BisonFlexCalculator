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

%start result

%% 

result: expr 
{
  extra_t* extra = calc_get_extra (scanner);
  extra->result = $$;
}

expr:
  expr '+' expr { $$ = $1 + $3; }
| expr '-' expr { $$ = $1 - $3; }
| expr '*' expr { $$ = $1 * $3; }
| expr '/' expr { $$ = $1 / $3; }
| '-' expr %prec UMINUS { $$ = -$2; }
| '(' expr ')' { $$ = $2; }
| NUMBER { $$ = $1; }
| 'x'
  {
      extra_t* extra = calc_get_extra (scanner);
      $$ = extra->x_value;
  }

%%