LLVM_CONFIG := llvm-config
LLVM_FLAGS := $(shell $(LLVM_CONFIG) --libs --cflags)

CC = gcc
CFLAGS = -Wall -Wextra -pedantic

llvm_module: parser.tab.o lex.yy.o llvm_module.o
	$(CC) -o llvm_module llvm_module.o parser.tab.o lex.yy.o $(LLVM_FLAGS) $(CFLAGS)

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l

parser.tab.o: parser.tab.c
	$(CC) -c parser.tab.c $(CFLAGS)

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c $(CFLAGS)

llvm_module.o: llvm_module.c
	$(CC) -c llvm_module.c $(CFLAGS)

clean:
	rm -f llvm_module parser.tab.* lex.yy.* *.o

result:
	llc -filetype=obj output.ll -o output.o
	gcc -o programa output.o -lm -no-pie