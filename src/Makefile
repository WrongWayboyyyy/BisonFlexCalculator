.PHONY: clean build run

version=arena
PREFIX = ..
right_bound = 101
step = 5
iter = 1000000
CSV_FOLDER = csv
BUILD_DIR = build
SRC_DIR = src



ifeq (${version},arena)
	EXTRA_VERSION_FLAG=_ARENA_VERSION_
endif
ifeq (${version},naive)
	EXTRA_VERSION_FLAG=_NAIVE_VERSION_
endif

LDFLAGS += -L/opt/homebrew/opt/llvm/lib -lpthread -lLLVM
CFLAGS += -I/opt/homebrew/opt/llvm/include -o ${PREFIX}/calc.out -D${EXTRA_VERSION_FLAG}

SRC = ast.c calc.tab.c lex.yy.c arena/arena.c main.c llvm-c/llvm-init.c
clean:
	@rm -f calc.tab.c
	@rm -f calc.tab.h
	@rm -f lex.yy.c

build: calc.l calc.y ast.h
	@bison -o calc.tab.c -d calc.y 
	@flex -o lex.yy.c calc.l 
	cc ${CFLAGS} ${SRC} ${LDFLAGS}

run: build
ifeq (${mode},benchmark)
	python3 ${PREFIX}/test.py ${PREFIX}/calc.out ${PREFIX}/csv/${version}.csv ${right_bound} ${step} ${iter} ${version}
else
	${PREFIX}/calc.out ${mode} ${version}
endif

	