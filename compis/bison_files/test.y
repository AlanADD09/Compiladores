%{
#include <stdio.h>
%}

%token NUM
%left '+' '-'
%left '*' '/'

%%

calc:   /* inicio de la regla */
        | calc expr '\n' { printf("Resultado: %d\n", $2); }
        ;

expr:   NUM         { $$ = $1; }
        | expr '+' expr  { $$ = $1 + $3; }
        | expr '-' expr  { $$ = $1 - $3; }
        | expr '*' expr  { $$ = $1 * $3; }
        | expr '/' expr  { $$ = $1 / $3; }
        | '(' expr ')'   { $$ = $2; }
        ;

%%

int yylex() {
    int c = getchar();
    if (c == EOF) return 0;
    if (c == '\n') return '\n';
    if (c == '+' || c == '-' || c == '*' || c == '/') return c;
    if (c >= '0' && c <= '9') {
        ungetc(c, stdin);
        scanf("%d", &yylval);
        return NUM;
    }
    return c;
}

int main() {
    yyparse();
    return 0;
}
