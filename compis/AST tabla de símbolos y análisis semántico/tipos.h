#ifndef TIPOS_H
#define TIPOS_H

/* La definición de tipo. Para nosotros, basta con una enumeración, en el caso
   de un compilador con tipos definidos por el usuario, es necesaria una tabla 
   de símbolos adicional.
*/
typedef enum{T_int,T_string,T_void}S_ty;

/* Lista de tipos:
   Necesitarás esto en el compilador para describir una función.  */

typedef struct S_tyList_ *S_tyList; 

struct S_tyList_{
  S_ty t;            /* Un tipo */
  S_tyList l;        /* seguido de una lista de tipos... */ 
};

S_tyList S_TyList(S_ty t, S_tyList l);


/* El ambiente en el que está definido un ID: */
typedef enum{S_global,S_local,S_parametro} S_ambiente;

/* La estructura que contendrá la asociación correspondiente en la 
   tabla de símbolos   */

typedef struct S_asoc_ *S_asoc;
struct S_asoc_{
  S_ambiente a;   /* ¿Dónde está definido?                                */
  S_ty t;         /* El tipo asociado al identificador                    */
  S_tyList largs; /* Una lista de argumentos, en caso de ser función      */
  unsigned despl; /* A las variables las referenciamos por desplazamiento */
};

S_asoc S_Asoc(S_ambiente a,S_ty t,S_tyList largs,unsigned despl);

#endif
