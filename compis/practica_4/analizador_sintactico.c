//Dominguez Duran Alan Axel -- 3CM12
#include <stdio.h>
#include <stdlib.h>

int yylex(); // Declaración de la función de análisis léxico generada por Flex

void ListaX();
void Lista();
int token;

void error() {
    fprintf(stderr, "Error de sintaxis\n");
    exit(1);
}

void Lista() {
    if (token == 'x') {
        token = yylex(); // Obtiene el siguiente token
        ListaX();
    } else {
        error();
    }
}

void ListaX() {
    if (token == ',') {
        token = yylex(); // Obtiene el siguiente token
        Lista();
    } else if (token == '$') {
        // Fin de la entrada
        return;
    } else {
        error();
    }
}

int main() {
    token = yylex(); // Inicializa el analizador léxico
    Lista();
    
    if (token == '$') {
        printf("Análisis sintáctico exitoso.\n");
    } else {
        error();
    }
    
    return 0;
}
