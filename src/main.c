#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "arena/arena.h"
#include "llvm-c/llvm-init.h"

#include "ast.h"
#include "naive.h"

int yylex ();
int yyparse (calc_args_t *);
extern void yy_scan_string (const char *str);
extern double fabs (double);
extern int yylineno;

typedef enum calc_mode_t {interactive, benchmark} calc_mode_t;

typedef enum calc_version_t {naive, ast, jit} calc_version_t;

void yyerror (calc_args_t *, const char *s);

int main (int argc, char **argv) {

    calc_mode_t calc_mode;
    calc_version_t calc_version;

    const char *mode = argv[1];
    if (!mode) {
        printf ("%s", "No mode selected");
        exit (EXIT_FAILURE);
    }
    else if (strcmp (mode, "benchmark") == 0) {
        calc_mode = benchmark; 
    }
    else if (strcmp (mode, "interactive") == 0) {
        calc_mode = interactive;
    }
    else {
        printf ("%s", "Unknown mode selected\n");
        exit (EXIT_FAILURE);
    }

    const char* version = argv[2];
    if (!version) {
        printf ("No version selected");
        exit (EXIT_FAILURE);
    }
    else if (strcmp (version, "naive") == 0) {
        calc_version = naive;
    } 
    else if (strcmp (version, "arena") == 0) {
        calc_version = ast;
    }
    else if (strcmp (version, "jit") == 0) {
        calc_version = jit;
    }
    else {
        printf("%s", "Unknown version selected\n");
        exit (EXIT_FAILURE);
    }

    const char *test_string;
    int iterations;

    if (calc_mode == benchmark) {
        if (argc < 5) {
            printf ("%s", "Too few arguments");
            return -1;
        }
        test_string = argv[3];
        iterations = atoi (argv[4]);
    }

    bool in_progress = true;
    calc_args_t args;
    if (calc_version == ast) {
        args.arena = malloc (sizeof (arena_t));
        arena_construct (args.arena);
    }

    LLVMModuleRef module;
    LLVMExecutionEngineRef engine;

    llvm_init(&module, &engine);

    while (in_progress) {
        if (calc_mode == interactive) {
            printf ("> ");
            yyparse (&args);
        }
        
        if (calc_mode == benchmark) {
            if (calc_version == naive) {
                for (int i = 0; i < iterations; ++i) {
                    yy_scan_string (test_string);
                    yyparse (&args);
                }   
            } else if (calc_version == ast) {

                yy_scan_string (test_string);
                yyparse (&args);
                for (int i = 0; i < iterations; ++i) {
                    printf ("%f\n", CALC_RESULT (0.0));
                }
            }
            in_progress = false;
        }
    }
    if (calc_version == ast) {
        arena_free (args.arena);
    }
    return 0;
}

void yyerror (calc_args_t *args, const char *s) {
    fprintf (stderr, "%d: error: ", yylineno);
    fprintf (stderr, "\n");
}