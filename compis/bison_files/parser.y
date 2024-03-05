%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%token NUM
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%%

calc:   /* Empty input */
    | calc expr '\n' { printf("Resultado: %d\n", $2); }
    ;

expr:   NUM           { $$ = $1; }
    | expr '+' expr  { $$ = $1 + $3; }
    | expr '-' expr  { $$ = $1 - $3; }
    | expr '*' expr  { $$ = $1 * $3; }
    | expr '/' expr  { 
        if ($3 == 0) {
            yyerror("División por cero.");
        }
        else {
            $$ = $1 / $3;
        }
    }
    | '(' expr ')'   { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    ;

%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}
