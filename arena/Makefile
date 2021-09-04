subpath = arena

clean:
	rm -f calc.tab.c
	rm -f calc.tab.h
	rm -f lex.yy.c

build: calc.l calc.y ${subpath}/ast.h
	bison -d calc.y
	flex calc.l
	cc -I${subpath} -o calc.out ${subpath}/ast.c calc.tab.c lex.yy.c ${subpath}/arena.c

run: build
	./calc.out ${mode} ${expr} ${repeats}

	