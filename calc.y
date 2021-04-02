%{
#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
int yylex();
int yyparse();
%}

%union {
    struct Node* a;
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
    | calclist exp EOL { printf("= %f\n", eval($2)); 
    treefree($2);
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
    | NUMBER {$$ = newnum($1); }
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