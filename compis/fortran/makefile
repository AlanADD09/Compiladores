cmp:
	flex fortran_lex.l
	gcc -o fortran_lex lex.yy.c -lfl
run:
	./fortran_lex
clean:
	rm -f fortran_lex lex.yy.c