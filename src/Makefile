.PHONY: clean build run

version = arena
PREFIX = ..
right_bound = 101
step = 5
iter = 1000000
CSV_FOLDER = csv
BUILD_DIR = build
SRC_DIR = src

clean:
	@rm -f calc.tab.c
	@rm -f calc.tab.h
	@rm -f lex.yy.c

build: calc.l calc.y ${version}/ast.h
	@bison -o calc.tab.c -d calc.y 
	@flex -o lex.yy.c calc.l 
	@cc -I${version} -o ${PREFIX}/calc.out ${version}/ast.c calc.tab.c lex.yy.c arena/arena.c

run: build clean
ifeq (${mode},benchmark)
	python3 ${PREFIX}/test.py ${PREFIX}/calc.out ${PREFIX}/csv/${version}.csv ${right_bound} ${step} ${iter} ${version}
else
	${PREFIX}/calc.out ${mode} ${version}
endif

	