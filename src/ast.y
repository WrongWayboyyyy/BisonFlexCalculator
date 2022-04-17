%code top {
#include "ast.h"
#include "ast.lex.h"
#include "ast_calc.h"

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
    extra_t* extra = ast_get_extra (scanner);
    *extra->result = eval (extra->arena);
}

expr:
  expr '+' expr { 
    extra_t* extra = ast_get_extra (scanner);
    $$ = newnode (extra->arena, '+', $1, $3); 
  }
| expr '-' expr { 
    extra_t* extra = ast_get_extra (scanner);
    $$ =  newnode (extra->arena, '-', $1, $3); 
  }
| expr '*' expr { 
    extra_t* extra = ast_get_extra (scanner);
    $$ =  newnode (extra->arena, '*', $1, $3); 
  }
| expr '/' expr { 
    extra_t* extra = ast_get_extra (scanner);
    $$ =  newnode (extra->arena, '/', $1, $3); 
  }
| '-' expr %prec UMINUS { 
    extra_t* extra = ast_get_extra (scanner);
    $$ = newnode (extra->arena, '|', $1, -1); 
  }
| '+' expr %prec UMINUS { 
    extra_t* extra = ast_get_extra (scanner);
    $$ = newnode (extra->arena, 'M', $1, -1); 
  }
| '(' expr ')' { $$ = $2; }
| NUMBER { 
    extra_t* extra = ast_get_extra (scanner);
    $$ = newnum (extra->arena, $1); 
}

%%