%{

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "ast.h"
#include "naive.h"
#include "jit.h"

int yylex ();

%}

%token NUMBER
%token EOL

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS
%param {calc_args_t *args}
%define api.value.type {calc_type_t}

%%

calclist: 
    | calclist exp EOL { CALC_RESULT ($2); return 0; }
    | calclist EOL { printf ("> "); }
;

exp:  exp '+' exp          { CALC_ADD ($$, $1, $3); }
    | exp '-' exp          { CALC_SUB ($$, $1, $3); }
    | exp '*' exp          { CALC_MUL ($$, $1, $3); }
    | exp '/' exp          { CALC_DIV ($$, $1, $3); }
    | '|' exp              { CALC_ABS ($$, $2); } 
    | '(' exp ')'          { $$ = $2; }
    | '-' exp %prec UMINUS { CALC_NEG ($$, $2); }
    | NUMBER               { CALC_NUM ($$, $1); }
;   

%%