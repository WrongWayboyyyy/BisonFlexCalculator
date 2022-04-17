%option 8bit reentrant bison-bridge
%option warn nounput never-interactive noyywrap
%option extra-type="void*"
%option prefix="jit_"
%{
#include "jit.h"
#include "jit.tab.h"
#define YY_NO_INPUT
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
"."?[0-9]+{EXP}? { 
    yylval->val = atof (yytext); 
    return NUMBER;
}
"//".*
[ \t]  { }
.      { printf("Mystery character %s\n", yytext); }

%%