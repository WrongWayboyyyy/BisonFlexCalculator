%option noyywrap nodefault yylineno
%{
#include "naive.h"
#include "arena/arena.h"
#include "calc.h"
#include "ast.h"
#include "jit.h"
#include "calc.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%
"+" | 
"-" |
"*" |
"/" |
"|" |
"(" |
")"  {return yytext[0]; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.val = atof(yytext); return NUMBER; }
\n     { return EOL; }
"//".*
[ \t]  { }
.      { printf("Mystery character %s\n", yytext); }

%%