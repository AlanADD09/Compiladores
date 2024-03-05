%{
#include <stdio.h>
#include <stdbool.h>
#include "errormsg.h"
#include "util.h"

extern int yylex();
void yyerror(const char *s) { fprintf(stderr, "%s\n", s); }
%}

%union {
    int ival;
    char *sval;
}

%token <sval> IDENTIFICADOR
%token <ival> TIPO_DATO_INT DEF_FUNCION SENTENCIA_IF SENTENCIA_WHILE RETORNO ASIGNACION PUNTO_Y_COMA LLAVE_INICIO LLAVE_FIN PARENTESIS

%%

program:
    /* definición de las reglas de análisis sintáctico */
    ;

%%

int main(int argc, char **argv) {
    yyparse();
    return 0;
}