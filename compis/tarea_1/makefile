cmp:
	flex lexer.l
	gcc -o lexer lex.yy.c -lfl
run:
	./lexer input.txt
clean:
	rm -f lexer lex.yy.c