%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

int yylex();

int result;
%}

%token DEF INT_TYPE RETURN PRINT OPEN_PAREN CLOSE_PAREN OPEN_BRACE CLOSE_BRACE SEMICOLON ASSIGN COMMA IDENTIFIER INTEGER_CONSTANT PLUS MINUS MULTIPLY DIVIDE EQUALS NOT_EQUALS GREATER GREATER_EQUAL LESS LESS_EQUAL
%type<intval> INTEGER_CONSTANT expression statement
%left PLUS MINUS
%left MULTIPLY DIVIDE

%start program

%union {
    char *strval;
    int intval;
    // Otros tipos si es necesario
}

%%

program : statement { $1; }
        ;

statement : RETURN expression SEMICOLON { $$ = $2; printf("Returning expression\n"); } 
          | RETURN INTEGER_CONSTANT SEMICOLON { $$ = $2; }
          | expression SEMICOLON { $$ = $1; printf("Expression without return\n"); }
          ;

expression : INTEGER_CONSTANT { $$ = $1; }
           | OPEN_PAREN expression CLOSE_PAREN { $$ = $2; }
           | expression PLUS expression { printf("Creating node for PLUS operation\n"); $$ = $1 + $3; }
           | expression MINUS expression { printf("Creating node for MINUS operation\n"); $$ = $1 - $3; }
           | expression MULTIPLY expression { printf("Creating node for MULTIPLY operation\n"); $$ = $1 * $3; }
           | expression DIVIDE expression { printf("Creating node for DIVIDE operation\n"); $$ = $1 / $3; }
           ;


%%

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}
