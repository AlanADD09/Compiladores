%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "parser.h"

int yylex();

ast* root = NULL;
ast* new_ast(int nodetype, ast* left, ast* right);
extern ast* root;

int result;
%}

%token DEF INT_TYPE RETURN PRINT OPEN_PAREN CLOSE_PAREN OPEN_BRACE CLOSE_BRACE SEMICOLON ASSIGN COMMA IDENTIFIER INTEGER_CONSTANT PLUS MINUS MULTIPLY DIVIDE EQUALS NOT_EQUALS GREATER GREATER_EQUAL LESS LESS_EQUAL
%type<intval> INTEGER_CONSTANT expression statement statement_list
%left PLUS MINUS
%left MULTIPLY DIVIDE

%start program

%union {
    char *strval;
    int intval;
    // Otros tipos si es necesario
}

%%

program : statement_list { root = $1; }
        ;

statement_list : statement
               | statement_list SEMICOLON statement
               ;

statement : RETURN expression { $$ = $2; }
          | RETURN INTEGER_CONSTANT { $$ = new_num($2); }
          ;

expression : INTEGER_CONSTANT { $$ = new_num($1); }
           | expression PLUS expression { $$ = new_ast('+', $1, $3); }
           | expression MINUS expression { $$ = new_ast('-', $1, $3); }
           | expression MULTIPLY expression { $$ = new_ast('*', $1, $3); }
           | expression DIVIDE expression { $$ = new_ast('/', $1, $3); }
           | OPEN_PAREN expression CLOSE_PAREN { $$ = $2; }
           ;

%%

ast* new_num(int value) {
    ast* node = (ast*)malloc(sizeof(ast));
    if (!node) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    node->nodetype = INTEGER_CONSTANT;
    node->value = value;
    return node;
}

ast* new_ast(int nodetype, ast* left, ast* right) {
    ast* node = (ast*)malloc(sizeof(ast));
    if (!node) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    node->nodetype = nodetype;
    node->left = left;
    node->right = right;
    return node;
}

int eval_ast(ast* node) {
    if (!node) {
        fprintf(stderr, "Invalid AST node\n");
        return 0;
    }

    if (node->nodetype == INTEGER_CONSTANT) {
        return node->value;
    }

    int left_val = eval_ast(node->left);
    int right_val = eval_ast(node->right);

    switch (node->nodetype) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return left_val / right_val;
        default:
            fprintf(stderr, "Invalid operation\n");
            return 0;
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
}
