%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include "arena_ast.h"
#include <stdbool.h>

int yylex();
int yyparse(arena*, node**);
extern void yy_scan_string(const char* str);

%}

%union {
    unsigned int a;
    double d;
}

%token <d> NUMBER
%token EOL

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS
%param { arena* arena } {node** root}

%type <a> exp

%code requires {
    #include "arena.h"
}

%%

calclist: 
    | calclist exp EOL { *root = arena->arena + $2; return 0; }
    | calclist EOL { printf("> "); }
;

exp: exp '+' exp {$$ = newast(arena, '+', $1, $3); }
    | exp '-' exp {$$ = newast(arena, '-', $1, $3); }
    | exp '*' exp {$$ = newast(arena, '*', $1, $3); }
    | exp '/' exp {$$ = newast(arena, '/', $1, $3); }
    | '|' exp {$$ = newast(arena, '|', $2, -1); } 
    | '(' exp ')' {$$ = $2; }
    | '-' exp %prec UMINUS {$$ = newast(arena, 'M', $2, -1); }
    | NUMBER {$$ = newnum(arena, $1); }
;   

%%

char* terminateString(char* str) {
    char* src = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(src, str);
    src[strlen(str)] = '\n';
    return src;
}

int main(int argc, char** argv) {

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

    if (strcmp(mode, "benchmark") == 0) {
        if (argc < 4) {
            printf("%s", "Bad arguments");
            return -1;
        }
        testString = terminateString(argv[2]);
        repeats = atoi(argv[3]);
        yy_scan_string(testString);
    }

    node* result;
    bool inProgress = true;
    while (inProgress) {
        arena* arena = malloc(sizeof(arena));
        arena_construct(arena);
        if (strcmp(mode, "interactive") == 0)
            printf("> ");
        
        yyparse(arena, &result);
        if (strcmp(mode, "benchmark") == 0) {
            for (int i = 0; i < repeats; ++i) {
                printf("%f\n" , eval(arena, result));
            }   
            inProgress = false;
        }
        else {
            printf("= %f (allocated: %i)\n", eval(arena, result), arena->allocated);
        }
        arena_free(arena);
    }
    return 0;
}


void yyerror (arena* arg, node** root, char* s) {
    fprintf(stderr, "%d: error: ", yylineno);
    fprintf(stderr, "\n");
}