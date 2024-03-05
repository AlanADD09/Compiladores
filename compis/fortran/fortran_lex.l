/* Escáner para un lenguaje de juguete al estilo de Fortran */

%option noyywrap

%{
/* Se necesita esto para la llamada a atof() m�s abajo */
#include <math.h>
#include "tokens.h"
typedef union lexema lexema;

union lexema{
  int i;
  float f;
  char s[200];
} u;

%}

DIGITO   [0-9]
ID       [a-zA-Z][a-zA-Z0-9]*

%%

{DIGITO}+              {u.i = atoi( yytext ); return INTEGER;}

{DIGITO}+"."{DIGITO}*  {u.f = atof( yytext ); return REAL;}

if                     {return IF;} 
then                   {return THEN;}
do                     {return DO;}
end                    {return END;}
subroutine             {return SUBROUTINE;}
function               {return FUNCTION;}

{ID}                   {strcpy(u.s, yytext); return ID;}

\+                     {return '+';}
\-                     {return '-';}
\*                     {return '*';}
\/                     {return '/';}
\^                     {return '^';}
\=                     {return '=';}
\:                     {return ':';}
\,                     {return ',';}
\(                     {return '(';}
\)                     {return ')';}

\!.*                   /* Se come una línea de comentarios */

[ \t\n]+               /* Se come los espacios en blanco */

.           printf( "Caracter no reconocido: %s\n", yytext );

%%

int main(int argc, char **argv)
{
int tok = 0;

   ++argv, --argc;  /* Se salta el nombre del programa */
   if (argc > 0)
      yyin = fopen(argv[0], "r");
   else
      yyin = stdin;

while ((tok = yylex())) {
   switch (tok) {
     case INTEGER:
        printf("Un entero: %d\n", u.i); break;
     case REAL:
        printf("Un real  : %g.2\n", u.f); break;
     case IF:
     case THEN:
     case DO:
     case END:
     case SUBROUTINE:
     case FUNCTION:
        printf("Una palabra clave: %s\n", yytext ); break;
     case ID:
        printf("Un identificador: %s\n", u.s); break;
     case '+':
     case '-':
     case '*':
     case '/':
     case '^':
        printf("Un operador: %s\n", yytext); break;
    case '=':
    case ':':
    case ',':
    case '(':
    case ')':
        printf("Un delimitador: %s\n", yytext); break;

   }

 }
   return 1;
}
