YACC=bison -Wall
LEX=flex
LDFLAGS+=-L/opt/homebrew/opt/llvm/lib -lpthread -lLLVM
CFLAGS+=-I/opt/homebrew/opt/llvm/include -Wall  -O2 -g

CC=cc

%.tab.h %.tab.c: %.y
	$(YACC) -d $<

%.lex.h %.lex.c: %.l
	$(LEX) --header-file=calc.lex.h -o $*.lex.c $<

main: main.o parser.tab.o calc.lex.o parser_calc.o ast.tab.o ast_calc.o tree.o arena.o
# ast.tab.o ast.lex.o jit.tab.o jit.lex.o parser_calc.o ast_calc.o jit_calc.o tree.o arena.o llvm.o

main.c: calc.lex.h parser.tab.h ast.tab.h

PHONY: clean

clean:
	$(RM) *.tab.[ch] *.lex.[ch] *.o main