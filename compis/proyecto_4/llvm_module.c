#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "parser.tab.h" 
#include <llvm-c/Core.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/ExecutionEngine.h>
#include "token.h"

#define MAX_INPUT_SIZE 100

void insert_token(int token, YYSTYPE value) {
    TokenInfo *new_token = (TokenInfo *)malloc(sizeof(TokenInfo));
    if (new_token == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para el token.\n");
        exit(EXIT_FAILURE);
    }
    
    new_token->token = token;
    if (token == RETURN || token == INT_TYPE) {
        new_token->value.strval = value.strval != NULL ? strdup(value.strval) : NULL;
    } else if (token == INTEGER_CONSTANT) {
        new_token->value.intval = value.intval;
    } else {
        // Para otros tokens que no almacenan valores
        new_token->value.strval = NULL;
    }
    
    new_token->next = head;
    head = new_token;
}

void printTokenValues() {
    TokenInfo *current = head;
    while (current != NULL) {
        switch (current->token) {
            case RETURN:
            case INT_TYPE:
                printf("Token: %d, Value: %s\n", current->token, current->value.strval);
                break;
            case INTEGER_CONSTANT:
                printf("Token: %d, Value: %d\n", current->token, current->value.intval);
                break;
            // Agrega casos para otros tipos de tokens si es necesario
            default:
                printf("Token: %d\n", current->token);
                break;
        }
        current = current->next;
    }
}

void print_token(int token, YYSTYPE value) {
    switch (token) {
        case RETURN:
            printf("RETURN ");
            if (value.strval != NULL) {
                printf("%s ", value.strval);
                insert_token(token, value);
                free(value.strval);
            } else {
                printf("null ");
            }
            break;
        case INT_TYPE:
            printf("INT_TYPE ");
            if (value.strval != NULL) {
                printf("%s ", value.strval);
                insert_token(token, value);
                free(value.strval);
            } else {
                printf("null ");
            }
            break;
        case INTEGER_CONSTANT:
            printf("INTEGER_CONSTANT ");
            printf("%d\n", value.intval);
            insert_token(token, value);
            break;
        case SEMICOLON:
            printf("SEMICOLON ");
            insert_token(token, value);
            printf("null\n");
            break;
        case PLUS:
            printf("PLUS\n");
            insert_token(token, value);
            break;
        case MINUS:
            printf("MINUS\n");
            insert_token(token, value);
            break;
        case MULTIPLY:
            printf("MULTIPLY\n");
            insert_token(token, value);
            break;
        case DIVIDE:
            printf("DIVIDE\n");
            insert_token(token, value);
            break;
        default:
            break;
    }
}

void generateLLVMIR() {
    printf("Entrando al modulo LLVM\n");
    LLVMInitializeAllTargetInfos();
    LLVMInitializeAllTargets();
    LLVMInitializeAllTargetMCs();
    LLVMInitializeAllAsmPrinters();
    LLVMInitializeAllAsmParsers();

    LLVMModuleRef module = LLVMModuleCreateWithName("SimpleModule");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    // Crear una función principal
    LLVMTypeRef mainFuncType = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef mainFunc = LLVMAddFunction(module, "main", mainFuncType);

    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(mainFunc, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    TokenInfo *current = head;

    LLVMValueRef result = NULL;

    while (current != NULL) {
        switch (current->token) {
            case INTEGER_CONSTANT:
                // Si encontramos un entero constante, lo usamos para crear un valor LLVM
                result = LLVMConstInt(LLVMInt32Type(), current->value.intval, 0);
                break;
            case PLUS:
                // Suma
                LLVMValueRef nextValue = LLVMConstInt(LLVMInt32Type(), current->next->value.intval, 0);
                result = LLVMBuildAdd(builder, result, nextValue, "addtmp");
                current = current->next;
                break;
            case MINUS:
                // Resta
                LLVMValueRef subValue = LLVMConstInt(LLVMInt32Type(), current->next->value.intval, 0);
                result = LLVMBuildSub(builder, result, subValue, "subtmp");
                current = current->next;
                break;
            case MULTIPLY:
                // Multiplicación
                LLVMValueRef mulValue = LLVMConstInt(LLVMInt32Type(), current->next->value.intval, 0);
                result = LLVMBuildMul(builder, result, mulValue, "multmp");
                current = current->next;
                break;
            case DIVIDE:
                // División
                LLVMValueRef divValue = LLVMConstInt(LLVMInt32Type(), current->next->value.intval, 0);
                result = LLVMBuildSDiv(builder, result, divValue, "divtmp");
                current = current->next;
                break;
            default:
                break;
        }
        current = current->next;
    }

    LLVMBuildRet(builder, result);
    LLVMPrintModuleToFile(module, "output.ll", NULL);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <archivo_de_entrada>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return EXIT_FAILURE;
    }

    char input[MAX_INPUT_SIZE];
    if (fgets(input, sizeof(input), file) == NULL) {
        perror("Error al leer el archivo");
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);

    yy_scan_string(input); // Establecer la cadena como entrada para el análisis
    int token;
    YYSTYPE value;
    do {
        token = yylex();
        value = yylval;
        // yyparse();

        print_token(token, value); // Imprimir tipo de token y valor reconocido
    } while (token != 0); // 0 indica el final del análisis

    printTokenValues();

    generateLLVMIR();

    // yyparse(); // Realizar el análisis sintáctico

    printf("Análisis completado.\n");

    return EXIT_SUCCESS; // Terminar la ejecución
}
