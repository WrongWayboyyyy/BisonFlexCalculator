%{

#include <stdio.h>
#include <string.h>
#include <ast.h>
#include <stdbool.h>
#include "arena/arena.h"

int yylex ();
int yyparse (arena_t*);
extern void yy_scan_string (const char* str);
extern double fabs (double);
extern int yylineno;
void yyerror (arena_t*, const char *s);

typedef enum calc_mode_t {interactive, benchmark} calc_mode_t;

typedef enum calc_version_t {naive, ast} calc_version_t;


%}

%token NUMBER
%token EOL

%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS
%param {arena_t* arena}

%%

calclist: 
    | calclist exp EOL { printf ("%f \n", CALC_RESULT ($2)); return 0; }
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

char* terminate_string (char* str) {
    char* src = malloc ((strlen (str) + 1) * sizeof (char));
    strcpy (src, str);
    src[strlen (str)] = '\n';
    return src;
}

int main (int argc, char** argv) {

    calc_mode_t calc_mode;
    calc_version_t calc_version;

    const char* mode = argv[1];
    if (!mode) {
        printf ("%s", "No mode selected");
        return -1;
    }
    else if (strcmp (mode, "benchmark") == 0) {
        calc_mode = benchmark; 
    }
    else if (strcmp (mode, "interactive") == 0) {
        calc_mode = interactive;
    }
    else {
        printf ("%s", "Unknown mode selected\n");
        return -1;
    }

    const char* version = argv[2];
    if (!version) {
        printf ("No version selected");
        return -1;
    }
    else if (strcmp (version, "naive") == 0) {
        calc_version = naive;
    } 
    else if (strcmp (version, "arena") == 0) {
        calc_version = ast;
    }
    else {
        printf("%s", "Unknown version selected\n");
        return -1;
    }

    const char* test_string;
    int iterations;

    if (calc_mode == benchmark) {
        if (argc < 5) {
            printf ("%s", "Too few arguments");
            return -1;
        }
        test_string = terminate_string (argv[3]);
        iterations = atoi (argv[4]);
    }

    bool in_progress = true;
    arena_t* arena;
    if (calc_version == ast) {
        arena = malloc (sizeof (arena_t));
        arena_construct (arena);
    }
    while (in_progress) {
        if (calc_mode == interactive) {
            printf ("> ");
            yyparse (arena);
        }
        
        if (calc_mode == benchmark) {
            if (calc_version == naive) {
                for (int i = 0; i < iterations; ++i) {
                    yy_scan_string (test_string);
                    yyparse (arena);
                }   
            } else if (calc_version == ast) {

                yy_scan_string (test_string);
                yyparse (arena);
                for (int i = 0; i < iterations; ++i) {
                    printf ("%f\n", CALC_RESULT (0.0));
                }
            }
            in_progress = false;
        }
    }
    if (calc_version == ast) {
        arena_free (arena);
    }
    return 0;
}

void yyerror (arena_t* arena, const char* s) {
    fprintf (stderr, "%d: error: ", yylineno);
    fprintf (stderr, "\n");
}