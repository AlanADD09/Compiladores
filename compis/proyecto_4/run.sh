#!/bin/bash

flex lexer.l
bison -d parser.y
gcc -o llvm_module llvm_module.c parser.tab.c lex.yy.c -Wall -Wextra -pedantic $(llvm-config --libs --cflags)
./llvm_module input.sp
llc -filetype=obj output.ll -o output.o
gcc -o programa output.o -lm -no-pie
./programa
echo $?