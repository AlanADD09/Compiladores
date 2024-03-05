%{
#include <stdio.h>
#include "parser.tab.h"
%}

%%

"def"           { return DEF; }
"int"           { return INT_TYPE; }
"return"        { return RETURN; }
"print"         { return PRINT; }
"("             { return OPEN_PAREN; }
")"             { return CLOSE_PAREN; }
"{"             { return OPEN_BRACE; }
"}"             { return CLOSE_BRACE; }
";"             { return SEMICOLON; }
"="             { return ASSIGN; }
","             { return COMMA; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULTIPLY; }
"/"             { return DIVIDE; }
"=="            { return EQUALS; }
"!="            { return NOT_EQUALS; }
">"             { return GREATER; }
">="            { return GREATER_EQUAL; }
"<"             { return LESS; }
"<="            { return LESS_EQUAL; }
[a-zA-Z][a-zA-Z0-9]*    { yylval.strval = strdup(yytext); return IDENTIFIER; }
[0-9]+          { yylval.intval = atoi(yytext); return INTEGER_CONSTANT; }
[\t\n ]+        ; // Ignore whitespace and tabs
.               { printf("Error: Caracter no reconocido '%s'\n", yytext); }

%%

int yywrap() {
    return 1;
}
