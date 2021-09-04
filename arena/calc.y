%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <ast.h>
#include <stdbool.h>

int yylex();
int yyparse();
extern void yy_scan_string(const char* str);
extern double fabs(double);
void yyerror(const char *s);


%}

%token NUMBER
%token EOL

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS
%code requires {
    #include <ast.h>
}


%%

calclist: 
    | calclist exp EOL { printf("%f", $2); }
    | calclist EOL { printf("> "); }
;

exp: exp '+' exp {CALC_ADD($$, $1, $3); }
    | exp '-' exp {CALC_SUB($$, $1, $3); }
    | exp '*' exp {CALC_MUL($$, $1, $3); }
    | exp '/' exp {CALC_DIV($$, $1, $3); }
    | '|' exp {CALC_ABS($$, $2); } 
    | '(' exp ')' {$$ = $2; }
    | '-' exp %prec UMINUS {CALC_NEG($$, $2); }
    | NUMBER {CALC_NUM($$, $1); }
;   

%%

char* terminateString(char* str) {
    char* src = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(src, str);
    src[strlen(str)] = '\n';
    return src;
}

int main(int argc, char** argv) {

    printf("> ");

    const char* mode = argv[1];
    int code;
    if (!mode) {
        printf("%s", "No mode selected");
        return -1;
    }
    if (strcmp(mode, "benchmark") == 0) {
        code = 1;
    }
    else
    if (strcmp(mode, "interactive") == 0) {
        code = 2;
    }
    else {
        printf("%s", "Unknown mode selected");
        return -1;
    }
    const char* testString;
    int repeats = 1;
    yyparse();

    // if (strcmp(mode, "benchmark") == 0) {
    //     if (argc < 4) {
    //         printf("%s", "Bad arguments");
    //         return -1;
    //     }
    //     testString = terminateString(argv[2]);
    //     repeats = atoi(argv[3]);
    //     yy_scan_string(testString);
    // }
    // node* result;

    // bool inProgress = true;
    // while (inProgress) {
    //     arena* arena = malloc(sizeof(arena));
    //     arena_construct(arena);
    //     if (strcmp(mode, "interactive") == 0)
    //         printf("> ");
        
    //     result = arena->arena + yyparse(arena);
    //     if (strcmp(mode, "benchmark") == 0) {
    //         for (int i = 0; i < repeats; ++i) {
    //             printf("%f\n" , eval(arena, result));
    //         }   
    //         inProgress = false;
    //     }
    //     else {
    //         printf("= %f (allocated: %i)\n", eval(arena, result), arena->allocated);
    //     }
    //     arena_free(arena);
    // }
    return 0;
}

void yyerror (const char* s) {
    fprintf(stderr, "%d: error: ", yylineno);
    fprintf(stderr, "\n");
}