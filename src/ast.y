%code top {
#include "ast.h"
#include "ast.lex.h"

static void ast_error (void* scanner, char* error) {}
}

%param {void* scanner}
%define api.prefix {ast_}
%define api.pure full

%token NUMBER

%left '+' '-'
%left '*' '/'
%precedence UMINUS

%defines

%start result

%% 

result: expr {
    AST_STYPE* result = ast_get_extra (scanner);
    *result = $1;
}

expr:
  expr '+' expr { $$ = newnode (args, '+', $1, $3); }
| expr '-' expr { $$ =  newnode (args, '-', $1, $3); }
| expr '*' expr { $$ = newnode (args, '*', $1, $3); }
| expr '/' expr { $$ = newnode (args, '/', $1, $3); }
| '-' expr %prec UMINUS { $$ = newnode (args, '|', ARG, -1); }
| '+' expr %prec UMINUS { $$ = newnode (args, 'M', ARG, -1); }
| '(' expr ')' { $$ = $2; }
| NUMBER { $$ = newnum (args, ARG); }


%%