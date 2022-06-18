%code top {
#include "jit.h"
#include "calc.lex.h"
#include "jit_calc.h"
#include "llvm.h"

static void jit_error (void* scanner, char* error) {}
}

%param {void* scanner}
%define api.prefix {jit_}
%define api.pure full
%define api.value.type {jit_value_t}

%token NUMBER

%left '+' '-'
%left '*' '/'
%precedence UMINUS

%defines

%start result

%% 

result: expr 
{
  extra_t* extra = calc_get_extra (scanner);
  LLVMBuildRet (extra->builder, $$.rvalue);
}

expr:
  expr '+' expr 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$.rvalue = LLVMBuildFAdd (extra->builder, $1.rvalue, $3.rvalue, "add");

  }
| expr '-' expr 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$.rvalue = LLVMBuildFSub (extra->builder, $1.rvalue, $3.rvalue, "sub");
  }
| expr '*' expr 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$.rvalue = LLVMBuildFMul (extra->builder, $1.rvalue, $3.rvalue, "mul");
  }
| expr '/' expr 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$.rvalue = LLVMBuildFDiv (extra->builder, $1.rvalue, $3.rvalue, "div");
  }
| '-' expr %prec UMINUS 
  { 
    extra_t* extra = calc_get_extra (scanner);
    $$.rvalue = LLVMBuildFNeg (extra->builder, $2.rvalue, "neg");
  }
| '|' expr %prec UMINUS 
  { 
    $$.rvalue = $2.rvalue;
  }
| '(' expr ')' { $$.rvalue = $2.rvalue; }
| NUMBER 
  { 
    $$.rvalue = LLVMConstReal (LLVMDoubleType (), $1.val);
  }
| 'x' 
  {
    extra_t* extra = calc_get_extra (scanner);
    $$.rvalue = extra->value;
  }
%%