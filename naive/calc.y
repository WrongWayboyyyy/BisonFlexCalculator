%{
#include <stdio.h>
#include <stdlib.h>
extern int yylex();
extern void yyerror();
extern int yylineno;
extern void yy_scan_string(const char* str);
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
    const char* testString = argv[1];
    for (int i = 0; i < 1000 * 1000; ++i) {
        yy_scan_string(testString);
        yyparse();
    }

    printf("> ");
    
}

void yyerror(char* s) {
    fprintf(stderr, "%d: error: ", yylineno);
    fprintf(stderr, "\n");
}