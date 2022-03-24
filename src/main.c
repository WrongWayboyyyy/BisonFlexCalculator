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
    printf("Mode selected: %s\n", mode);

    const char* version = argv[2];
    if (!version) {
        printf ("No version selected");
        exit (EXIT_FAILURE);
    }
    else if (strcmp (version, "naive") == 0) {
        calc_version = naive;
    } 
    else if (strcmp (version, "ast") == 0) {
        calc_version = ast;
    }
    else if (strcmp (version, "jit") == 0) {
        calc_version = jit;
    }
    else {
        printf("%s", "Unknown version selected\n");
        exit (EXIT_FAILURE);
    }
    printf("Version selected: %s\n", version);

    const char *test_string;
    int iterations;

    if (calc_mode == benchmark) {
        if (argc < 5) {
            printf ("%s", "Error: Too few arguments");
            return -1;
        }
        test_string = argv[3];
        printf("Test string: %s", test_string);
        iterations = atoi (argv[4]);
        printf("Number of iterations: %d\n", iterations);
    }

    bool in_progress = true;
    calc_args_t *args = malloc (sizeof (calc_args_t));

    if (!args) {
        printf("Error: Bad arguments allocation\n");
        exit(EXIT_FAILURE);
    }

    if (calc_version == ast) {
        args->arena = malloc (sizeof (arena_t));
        arena_construct (args->arena);
        if (!args->arena) {
            printf("Error: Bad arena allocation\n");
            exit(EXIT_FAILURE);
        }
    }

    LLVMModuleRef module;
    LLVMExecutionEngineRef engine;
    LLVMBuilderRef builder;
    LLVMValueRef value;

    while (in_progress) {
        if (calc_mode == interactive) {
            if (calc_version == jit) {
                llvm_init (&module, &engine, &builder, &value);
                    args->builder = builder;
                    args->value = value;
            }

            printf ("> ");
            yyparse (args);
            if (calc_version == jit) {
                double (*f)(int) = LLVMGetFunctionAddress (engine, "func");
                args->result = f(0);

            }
            
            printf("%f\n", args->result);
        }

        if (calc_mode == benchmark) {
            yy_scan_string (test_string);
            yyparse (args);
            if (calc_version == naive) {
                for (int i = 0; i < iterations; ++i) {
                    yy_scan_string (test_string);
                    yyparse (args);
                }   
            } else if (calc_version == ast) {
                for (int i = 0; i < iterations; ++i) {
                    eval (args);
                }
            } else if (calc_version == jit) {
                for (int i = 0; i < iterations; ++i) {
                    int (*f)(int) = LLVMGetFunctionAddress (engine, "func");
                    f(0);
                }

            }
            in_progress = false;
        }
    }
    if (calc_version == ast) {
        arena_free (args->arena);
    }

    llvm_verify (&module, &engine);
    return 0;
}

void yyerror (calc_args_t *args, const char *s) {
    fprintf (stderr, "%d: Error: ", yylineno);
    fprintf (stderr, "\n");
}