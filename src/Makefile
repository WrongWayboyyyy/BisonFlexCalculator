YACC=bison -Wall -Werror
LEX=flex
CFLAGS+=-Wall -Werror -O2 -g

CC=cc

%.tab.h %.tab.c: %.y
	$(YACC) -d $<

%.lex.h %.lex.c: %.l
	$(LEX) --header-file=$*.lex.h -o $*.lex.c $<

main: main.o expr.tab.o expr.lex.o expr_calc.o

main.c: expr.lex.h expr.tab.h

PHONY: clean

clean:
	$(RM) *.tab.[ch] *.lex.[ch] *.o main