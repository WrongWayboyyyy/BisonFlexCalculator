YACC=bison -Wall -Werror
LEX=flex
LDFLAGS+=-L/opt/homebrew/opt/llvm/lib -lpthread -lLLVM
CFLAGS+=-I/opt/homebrew/opt/llvm/include -Werror -O2 -g

CC=cc

%.tab.h %.tab.c: %.y
	$(YACC) -d $<

%.lex.h %.lex.c: %.l
	$(LEX) --header-file=calc.lex.h -o $*.lex.c $<

main: main.o calc.lex.o parser.tab.o parser_calc.o ast.tab.o ast_calc.o jit.tab.o jit_calc.o tree.o arena.o llvm.o

main.c: calc.lex.h parser.tab.h ast.tab.h jit.tab.h

.PHONY: clean

clean:
	$(RM) *.tab.[ch] *.lex.[ch] *.o main