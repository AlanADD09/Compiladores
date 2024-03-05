#include <stdio.h>
#include <stdlib.h>

typedef struct TokenInfo {
    int token;
    union {
        char *strval;
        int intval;
    } value;
    struct TokenInfo *next;
} TokenInfo;

TokenInfo *head = NULL; // Esta variable global almacenará el inicio de la lista
