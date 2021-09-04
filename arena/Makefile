clean:
	rm calc.tab.c
	rm calc.tab.h
	rm lex.yy.c
	rm calc.out

build: calc.l calc.y arena_ast.h
	bison -d calc.y
	flex calc.l
	cc -o calc.out calc.tab.c lex.yy.c arena_ast.c arena.c

run: build
	./calc.out ${mode} ${expr} ${repeats}

	