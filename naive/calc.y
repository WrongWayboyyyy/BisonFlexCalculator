%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyparse();
void yyerror();
int yylineno;
%}

%union {
    double d;
}

%token <d> NUMBER
%token EOL

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <d> exp

%%

calclist: 
    | calclist exp EOL { printf("= %f\n", $2); 
    printf("> ");
    }
    | calclist EOL { printf("> "); }
;

exp:  exp '+' exp {$$ = $1 + $3; }
    | exp '-' exp {$$ = $1 + $3; }
    | exp '*' exp {$$ = $1 * $3; }
    | exp '/' exp {$$ = $1 / $3; }
    | '|' exp {$$ = $2 >= 0? $2 : - $2; }
    | '(' exp ')' {$$ = $2; }
    | '-' exp %prec UMINUS { $$ = -$2; }
    | NUMBER {$$ = $1; }
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