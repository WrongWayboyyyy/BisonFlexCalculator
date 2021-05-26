%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
int yylex();
int yyparse();
%}

%union {
    struct node* a;
    double d;
}

%token <d> NUMBER
%token EOL

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp

%%

calclist: 
    | calclist exp EOL { 
        for (int i = 0; i < 1000 * 1000; ++i) {
            eval($2)); 
        }  
    printf("> ");
    }
    | calclist EOL { printf("> "); }
;

exp: exp '+' exp {$$ = newast('+', $1, $3); }
    | exp '-' exp {$$ = newast('-', $1, $3); }
    | exp '*' exp {$$ = newast('*', $1, $3); }
    | exp '/' exp {$$ = newast('/', $1, $3); }
    | '|' exp {$$ = newast('|', $2, NULL); }
    | '(' exp ')' {$$ = $2; }
    | '-' exp %prec UMINUS { $$ = newast('M', $2, NULL); }
    | NUMBER {printf("%c", $1);$$ = newnum($1); }
;   

%%

int main(int argc, char** argv) {
    printf("> ");
    return yyparse();
}

void yyerror(char* s) {
    fprintf(stderr, "%d: error: ", yylineno);
    fprintf(stderr, "\n");
}