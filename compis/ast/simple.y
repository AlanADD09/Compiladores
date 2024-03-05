%{
/* simple.y: Contiene los inicios de una especificacion para usarse en bison*/

#include <stdio.h>
#include "util.h"
#include "errormsg.h"
#include "tokens.h"
#include "tree.h"

EXP *ast; //Aqu� guardaremos el AST para comunicarlo 
          //al main
int yylex(void); /* C necesita conocer el prototipo de la funci�n de  */
		 /* An�lisis L�xico                                    */

void yyerror(char *s)
{
  EM_error(EM_tokPos, "%s", s);
}
%}


%union{
  int ival;
  char *sval;
  struct EXP *exp;
};
%type <exp> program exp
%token <ival> INT
%token DESPLIEGA
%left '+'
%left '*'

        
%start program

/* A continuaci�n la gram�tica */
                                 
%%

program: exp {ast=$1;}

exp: INT {$$=makeEXP_intLiteral($1);}
      //| exp + exp {$$=makeEXP_KindAddition($1,$3);}
   ;


