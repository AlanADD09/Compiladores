//Alan Axel Dominguez Duran  3CM12
%{
#include <stdio.h>
int linea = 1;
%}

%option noyywrap

%%

[ \t]+     /* Ignorar espacios en blanco y tabuladores */
[\r\n]     { linea++; } /* Contar líneas nuevas */
if|else    { printf("Palabra clave: %s\n", yytext); }

[_a-z][_a-z0-9]*   { printf("Identificador: %s\n", yytext); }

[0-9]+              { printf("Número entero: %s\n", yytext); }
[0-9]*\.[0-9]+      { printf("Número de punto flotante: %s\n", yytext); }

.   { printf("Token no reconocido: %s en línea %d\n", yytext, linea); }

%%

int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* archivo = fopen(argv[1], "r");
        if (archivo) {
            yyin = archivo;
        } else {
            printf("No se pudo abrir el archivo: %s\n", argv[1]);
            return 1;
        }
    }

    yylex();
    return 0;
}
