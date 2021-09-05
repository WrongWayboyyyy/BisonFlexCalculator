version = arena

clean:
	@rm -f calc.tab.c
	@rm -f calc.tab.h
	@rm -f lex.yy.c

build: calc.l calc.y ${version}/ast.h
	@bison -d calc.y
	@flex calc.l
	@cc -I${version} -o calc.out ${version}/ast.c calc.tab.c lex.yy.c arena/arena.c

run: build clean
	./calc.out ${mode} ${version} ${expr} ${repeats}

	