%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokens.h"
#include "util.h"

int comentario_abierto = 0;
int dentro_bloque = 0;

%}

%option noyywrap

%x COMENTARIO

%%
[a-zA-Z_][a-zA-Z0-9_]* {
    printf("Token: IDENTIFICADOR, Valor: %s\n", yytext);
    if (dentro_bloque) {
        int valor = buscarVariableLocal(yytext);
        if (valor == -1) {
            buscarVariableOFuncionGlobal(yytext);
        } else {
            printf("Valor local: %d\n", valor);
        }
    }
    return IDENTIFICADOR;
}

[[:space:]]*int[[:space:]]* {
    printf("Token: TIPO_DATO_INT: %s\n", yytext);
    return TIPO_DATO_INT;
}

[[:space:]]*"def"[[:space:]]* {
    printf("Token: DEF_FUNCION: %s\n", yytext);
    return DEF_FUNCION;
}

[[:space:]]*"if" {
    printf("Token: SENTENCIA_IF: %s\n", yytext);
    return SENTENCIA_IF;
}

[[:space:]]*"while" {
    printf("Token: SENTENCIA_WHILE: %s\n", yytext);
    return SENTENCIA_WHILE;
}

[[:space:]]*"return" {
    printf("Token: RETORNO: %s\n", yytext);
    return RETORNO;
}

[a-zA-Z_][a-zA-Z0-9_]*[[:space:]]*=[[:space:]]*[^;]+; {
    printf("Token: ASIGNACION, Valor: %s\n", yytext);
    if (dentro_bloque) {
        char nombre[100];
        int valor;
        sscanf(yytext, "%s = %d;", nombre, &valor);
        agregarVariableLocal(nombre, valor);
    }
    return ASIGNACION;
}

";" {
    if (dentro_bloque) {
        printf("Token: PUNTO_Y_COMA: %s\n", yytext);
    }
    return PUNTO_Y_COMA;
}

"{" {
    dentro_bloque++;
    struct Bloque* nuevoBloque = malloc(sizeof(struct Bloque));
    nuevoBloque->variables = NULL;
    nuevoBloque->funciones = NULL;
    nuevoBloque->siguiente = pilaBloques;
    pilaBloques = nuevoBloque;
    printf("Token: LLAVE_INICIO: %s\n", yytext);
    return LLAVE_INICIO;
}

"}" {
    dentro_bloque--;
    if (dentro_bloque < 0) {
        printf("Error: Llave de cierre sin bloque abierto\n");
    } else {
        printf("Token: LLAVE_FIN: %s\n", yytext);
        // Eliminar el bloque actual de la pila
        struct Bloque* bloqueAnterior = pilaBloques;
        pilaBloques = pilaBloques->siguiente;
        free(bloqueAnterior);
    }
    return LLAVE_FIN;
}

"(" {
    if (dentro_bloque) {
        printf("Token: PARENTESIS: %s\n", yytext);
    }
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