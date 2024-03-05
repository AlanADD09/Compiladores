#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "errormsg.h"
#include "y.tab.h"

YYSTYPE yylval;

int yylex(void); /* prototype for the lexing function */

string tokname(int tok);
/*char *tokname(inmt*/

string toknames[] = {"ID", "STRING", "INT","DESPLIEGA","SI",
                     "OTRO","AND","OR","NOT","DIFER","IGUAL"};


string tokname(tok) {
  return tok<258 || tok>299 ? "TOKEN NO VALIDO" : toknames[tok-258];
}

int main(int argc, char **argv) {
 string fname; int tok;
 if (argc!=2) {fprintf(stderr,"uso: driver archivo.simple\n"); exit(1);}
 fname=argv[1];
 EM_reset(fname);
 for(;;) {
   tok=yylex();
   if (tok==0) break;
   else if(tok<=255)
     printf("%c \n",tok);
     else
       switch(tok) {
         case ID: case STRING:
           printf("%10s %4d %s\n",tokname(tok),0,yylval.sval);
           break;
         case INT:
           printf("%10s %4d %d\n",tokname(tok),0,yylval.ival);
           break;
         default:
           printf("%10s %4d\n",tokname(tok),0);
       }
 }
 return 0;

}
