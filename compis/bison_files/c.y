%{
#include <stdio.h>
%}

%token INT CHAR VOID FLOAT NUM ID WHILE

%left '+' '-'
%left '>' '<' '=' NE

%%

programa : declaracionFuncion programa
         | epsilon
         ;

declaracionFuncion : tipo ID '(' listaParam ')' '{' listaInst '}'
                  ;

tipo : INT
     | CHAR
     | VOID
     | FLOAT
     ;

listaParam : param ',' listaParam
           | param
           | epsilon
           ;

param : tipo ID
      ;

listaInst : instruccion listaInst
          | epsilon
          ;

instruccion : declaracionVariable ';'
            | asignacion ';'
            | invocacionFuncion ';'
            | whileStmt
            ;

declaracionVariable : tipo ID
                   ;

asignacion : ID '=' expAritmetica
          ;

invocacionFuncion : ID '(' listaExp ')'
                 ;

listaExp : expAritmetica ',' listaExp
         | expAritmetica
         | epsilon
         ;

whileStmt : WHILE '(' expLogica ')' '{' listaInst '}'
          ;

expAritmetica : ID
             | NUM
             | expAritmetica '+' expAritmetica
             | expAritmetica '-' expAritmetica
             | '(' expAritmetica ')'
             ;

expLogica : expAritmetica '>' expAritmetica
          | expAritmetica '<' expAritmetica
          | expAritmetica '=' expAritmetica
          | expAritmetica NE expAritmetica
          | '(' expLogica ')'
          ;

epsilon : /* empty */
        ;

%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
