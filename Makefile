calc.out: calc.l calc.y structure.h
	bison -d calc.y
	flex calc.l
	cc -o $@ calc.tab.c lex.yy.c structure.c