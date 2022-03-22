%option noyywrap nodefault yylineno
%{
#include "arena/arena.h"
#include "calc.h"
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
"."?[0-9]+{EXP}? { yylval = atof(yytext); return NUMBER; }
\n     { return EOL; }
"//".*
[ \t]  { }
.      { printf("Mystery character %s\n", yytext); }

%%