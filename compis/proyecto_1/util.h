#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar las variables y sus valores
struct Variable {
    char nombre[100];
    int valor;
    struct Variable* siguiente;
};

struct Funcion {
    char nombre[100];
    struct Variable* parametros;
    struct Funcion* siguiente;
};

struct Variable* variables = NULL;
struct Funcion* funciones = NULL;

// Pila para manejar el alcance de las variables y funciones
struct Bloque {
    struct Variable* variables;
    struct Funcion* funciones;
    struct Bloque* siguiente; // Apuntador al bloque anterior
};

struct Bloque* pilaBloques = NULL;

// Función para agregar una variable al mapa del bloque actual
void agregarVariableLocal(const char* nombre, int valor) {
    struct Variable* nuevaVariable = malloc(sizeof(struct Variable));
    nuevaVariable->valor = valor;
    strncpy(nuevaVariable->nombre, nombre, 100);
    nuevaVariable->siguiente = pilaBloques->variables;
    pilaBloques->variables = nuevaVariable;
}

// Función para buscar una variable en el mapa del bloque actual
int buscarVariableLocal(const char* nombre) {
    struct Variable* actual = pilaBloques->variables;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            return actual->valor;
        }
        actual = actual->siguiente;
    }
    return -1; // Variable no encontrada en el bloque actual
}

// Función para agregar una función al mapa del bloque actual
void agregarFuncionLocal(const char* nombre, struct Variable* parametros) {
    struct Funcion* nuevaFuncion = malloc(sizeof(struct Funcion));
    strncpy(nuevaFuncion->nombre, nombre, 100);
    nuevaFuncion->parametros = parametros;
    nuevaFuncion->siguiente = pilaBloques->funciones;
    pilaBloques->funciones = nuevaFuncion;
}

// Función para buscar una función en el mapa del bloque actual
struct Funcion* buscarFuncionLocal(const char* nombre) {
    struct Funcion* actual = pilaBloques->funciones;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL; // Función no encontrada en el bloque actual
}

// Función para agregar una variable o función al mapa global
void agregarVariableGlobal(const char* nombre, int valor) {
    struct Variable* nuevaVariable = malloc(sizeof(struct Variable));
    nuevaVariable->valor = valor;
    strncpy(nuevaVariable->nombre, nombre, 100);
    nuevaVariable->siguiente = variables;
    variables = nuevaVariable;
}

void agregarFuncionGlobal(const char* nombre, struct Variable* parametros) {
    struct Funcion* nuevaFuncion = malloc(sizeof(struct Funcion));
    strncpy(nuevaFuncion->nombre, nombre, 100);
    nuevaFuncion->parametros = parametros;
    nuevaFuncion->siguiente = funciones;
    funciones = nuevaFuncion;
}

// Función para buscar una variable o función en el mapa global
void buscarVariableOFuncionGlobal(const char* nombre) {
    struct Variable* variable = variables;
    struct Funcion* funcion = funciones;
    while (variable != NULL) {
        if (strcmp(variable->nombre, nombre) == 0) {
            printf("Variable global encontrada: %s\n", variable->nombre);
            return;
        }
        variable = variable->siguiente;
    }
    while (funcion != NULL) {
        if (strcmp(funcion->nombre, nombre) == 0) {
            printf("Función global encontrada: %s\n", funcion->nombre);
            return;
        }
        funcion = funcion->siguiente;
    }
    printf("Error: Variable o función no declarada: %s\n", nombre);
}

#endif // UTIL_H