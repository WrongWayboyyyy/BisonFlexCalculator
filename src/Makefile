YACC=bison -Wall -Werror
LEX=flex
CFLAGS+=-Wall -Werror -O2 -g

CC=cc

BUILD_DIR=build

%.tab.h %.tab.c: %.y
	$(YACC) -d $<

%.lex.h %.lex.c: %.l
	$(LEX) --header-file=$*.lex.h -o $*.lex.c $<

%.o: %.c
	$(CC) -c -o $(BUILD_DIR)/$@ $< 

main: main.o expr.tab.o expr.lex.o
	${CC} -o $(BUILD_DIR)/main $(BUILD_DIR)/*.o

main.c: expr.lex.h expr.tab.h

PHONY: clean

clean:
	$(RM) *.tab.[ch] *.lex.[ch] *.o main