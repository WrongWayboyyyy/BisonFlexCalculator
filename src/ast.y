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
  expr '+' expr { 
    arena_t* extra = ast_get_extra (scanner);
    $$ = newnode (extra, '+', $1, $3); 
  }
| expr '-' expr { 
    arena_t* extra = ast_get_extra (scanner);
    $$ =  newnode (extra, '-', $1, $3); 
  }
| expr '*' expr { 
    arena_t* extra = ast_get_extra (scanner);
    $$ =  newnode (extra, '*', $1, $3); 
  }
| expr '/' expr { 
    arena_t* extra = ast_get_extra (scanner);
    $$ =  newnode (extra, '/', $1, $3); 
  }
| '-' expr %prec UMINUS { 
    arena_t* extra = ast_get_extra (scanner);
    $$ = newnode (extra, '|', $1, -1); 
  }
| '+' expr %prec UMINUS { 
    arena_t* extra = ast_get_extra (scanner);
    $$ = newnode (extra, 'M', $1, -1); 
  }
| '(' expr ')' { $$ = $2; }
| NUMBER { 
    arena_t* extra = ast_get_extra (scanner);
    $$ = newnum (extra, $1); 
}


%%