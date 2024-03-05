cmp:
	flex c_lex.l
	gcc -o c_lex lex.yy.c -lfl
run:
	./c_lex
clean:
	rm -f c_lex lex.yy.c