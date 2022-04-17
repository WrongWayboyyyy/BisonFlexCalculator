YACC=bison -Wall
LEX=flex
LDFLAGS+=-L/opt/homebrew/opt/llvm/lib -lpthread -lLLVM
CFLAGS+=-I/opt/homebrew/opt/llvm/include -Wall  -O2 -g

CC=cc

%.tab.h %.tab.c: %.y
	$(YACC) -d $<

%.lex.h %.lex.c: %.l
	$(LEX) --header-file=$*.lex.h -o $*.lex.c $<

main: main.o expr.tab.o expr.lex.o ast.tab.o ast.lex.o jit.tab.o jit.lex.o expr_calc.o ast_calc.o jit_calc.o tree.o arena.o llvm.o

main.c: expr.lex.h expr.tab.h ast.lex.h ast.tab.h jit.lex.h jit.tab.h

PHONY: clean

clean:
	$(RM) *.tab.[ch] *.lex.[ch] *.o main