%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

int comentario_abierto = 0;
int dentro_bloque = 0;

%}

%option noyywrap

%x COMENTARIO

%%
[a-zA-Z_][a-zA-Z0-9_]* {
    printf("Token: IDENTIFICADOR, Valor: %s\n", yytext);
    return IDENTIFICADOR;
}

"int" {
    printf("Token: TIPO_DATO_INT: %s\n", yytext);
    return TIPO_DATO_INT;
}

"def" {
    printf("Token: DEF_FUNCION: %s\n", yytext);
    return DEF_FUNCION;
}

"if" {
    printf("Token: SENTENCIA_IF: %s\n", yytext);
    return SENTENCIA_IF;
}

"while" {
    printf("Token: SENTENCIA_WHILE: %s\n", yytext);
    return SENTENCIA_WHILE;
}

"return" {
    printf("Token: RETORNO: %s\n", yytext);
    return RETORNO;
}

[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*=[[:space:]]*[^;]+; {
    printf("Token: ASIGNACION, Valor: %s\n", yytext);
    return ASIGNACION;
}

";" {
    printf("Token: PUNTO_Y_COMA: %s\n", yytext);
    return PUNTO_Y_COMA;
}

"{" {
    printf("Token: LLAVE_INICIO: %s\n", yytext);
    return LLAVE_INICIO;
}

"}" {
    printf("Token: LLAVE_FIN: %s\n", yytext);
    return LLAVE_FIN;
}

"(" {
    printf("Token: PARENTESIS: %s\n", yytext);
    return PARENTESIS;
}

<COMENTARIO>[^-\n]+ {
    // Manejar comentarios
}

<COMENTARIO>"---" {
    if (comentario_abierto > 1) {
        comentario_abierto--;
    }
    else {
        comentario_abierto = 0;
        BEGIN(INITIAL);
    }
}

. {
    // Ignorar otros caracteres fuera de los comentarios
}

%%

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s archivo_de_entrada\n", argv[0]);
        return 1;
    }

    FILE* archivo = fopen(argv[1], "r");
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    yyin = archivo;

    int token;
    while ((token = yylex()) != 0) {
        // No es necesario hacer nada aquí, ya que la acción de impresión está en las reglas
    }

    fclose(archivo);

    return 0;
}