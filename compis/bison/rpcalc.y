/* Calculadora de notación polaca inversa. */
%{
#define YYSTYPE double
#include <math.h>
#include <stdio.h>
%}

%token NUM
%left '+' '-'
%left '*' '/'
%right '^'
%left 'n'

%% /* A continuación las reglas gramaticales y las acciones */

input:
    /* vacío */
    | input line
    ;

line:
    '\n'
    | exp '\n' { printf("\t%.10g\n", $1); }
    ;

exp:
    NUM { $$ = $1; }
    | '-' exp %prec 'n' { $$ = -$2; }
    | exp '+' exp { $$ = $1 + $3; }
    | exp '-' exp { $$ = $1 - $3; }
    | exp '*' exp { $$ = $1 * $3; }
    | exp '/' exp { $$ = $1 / $3; }
    | exp '^' exp { $$ = pow($1, $3); }
    | '(' exp ')' { $$ = $2; }
    ;

%%

/* El analizador léxico devuelve un número en coma
flotante (double) en la pila y el token NUM, o el
carácter ASCII leído si no es un número. Ignora
todos los espacios en blanco y tabuladores,
devuelve 0 como EOF. */
#include <ctype.h>

int yylex() {
    int c;
    /* Ignora los espacios en blanco */
    while ((c = getchar()) == ' ' || c == '\t')
        ;
    /* Procesa números */
    if (c == '.' || isdigit(c))
    {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUM;
    }
    /* Devuelve fin-de-fichero */
    if (c == EOF)
        return 0;
    /* Devuelve caracteres simples */
    return c;
}

void yyerror(char *s) /* Llamada por yyparse ante un error */ {
    printf("%s\n", s);
}

int main() {
    yyparse();
    return 0;
}
