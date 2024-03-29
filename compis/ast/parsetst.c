#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "errormsg.h"
#include "tree.h"
#include "pretty.h"

extern int yyparse(void);
extern EXP *ast;
void parse(string fname) 
{EM_reset(fname);
 if (yyparse() == 0){ /* Funcion� el an�lisis sint�ctico correctamente */
   fprintf(stderr,"Programa Simple sintacticamente correcto!\n");
 }
 else fprintf(stderr,"Programa Simple con errores\n");
}

int main(int argc, char **argv) {
 if (argc!=2) {fprintf(stderr,"uso %s archivo\n",argv[0]); exit(1);}
 parse(argv[1]);
 prettyEXP(ast);
 return 0;
}
