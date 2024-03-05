%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include "tokens.h"

typedef union lexema lexema;

union lexema {
    int i;
    float f;
    char s[200];
} u;

%}

DIGITO   [0-9]
ID       [a-zA-Z][a-zA-Z0-9]*

%%

{DIGITO}+              {u.i = atoi(yytext); return NUM;}
{DIGITO}+"."{DIGITO}*  {u.f = atof(yytext); return NUM;}

int|char|void|float    {strcpy(u.s, yytext); return ID;}

{ID}                   {strcpy(u.s, yytext); return ID;}

"+"                    {return PLUS;}
"-"                    {return MINUS;}
"*"                    {return TIMES;}
"/"                    {return DIVIDE;}
"="                    {return ASSIGN;}
";"                    {return SEMICOLON;}
","                    {return COMMA;}
"("                    {return LPAREN;}
")"                    {return RPAREN;}
"while"                {return WHILE;}
"if"                   {return IF;}
"<"                    {return LTHAN;}
">"                    {return GTHAN;}
"=="                   {return EQUALS;}
"!="                   {return NEQUALS;}

[ \t\n]+               /* Se come los espacios en blanco */

.           printf("Caracter no reconocido: %s\n", yytext);

%%

int main(int argc, char **argv) {
    int tok = 0;

    ++argv, --argc;  /* Se salta el nombre del programa */
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

    while ((tok = yylex())) {
        switch (tok) {
            case NUM:
                printf("Un número: %d\n", u.i); break;
            case ID:
                printf("Un identificador: %s\n", u.s); break;
            case PLUS:
            case MINUS:
            case TIMES:
            case DIVIDE:
            case ASSIGN:
            case SEMICOLON:
            case COMMA:
            case LPAREN:
            case RPAREN:
            case WHILE:
            case IF:
            case LTHAN:
            case GTHAN:
            case EQUALS:
            case NEQUALS:
                printf("Token: %s\n", yytext); break;
            default:
                printf("Caracter no reconocido: %s\n", yytext);
        }
    }
    return 0;
}