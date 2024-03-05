%{
#include <string.h>
#include "util.h"
#include "y.tab.h"
#include "errormsg.h"

int charPos=1;

extern YYSTYPE yylval;

int yywrap(void)
{
 charPos=1;
 return 1;
}


#define MAX_STR_CONST   256
char string_buf[MAX_STR_CONST];
char *string_buf_ptr;

%}


%%



" "      {continue;}
\n       {continue;}
","      {return ',';}
despliega  {return DESPLIEGA;}

 /*<<EOF>> {printf("\nFin de Archivo encontrado."); exit(0); }*/

.        {printf("token ilegal\n");}
