/* Definiciones para los árboles de sintaxis abstracta */
/* Creado por Ricardo F. Díaz Santiago.                */ 

#ifndef SLPAU_H
#define SLPAU_H

#include "symbol.h"

/* Un nodo de árbol de Sintaxis Abstracta es una sentencia ó una expresion */
/* Declaramos los apuntadores correspondientes.                            */

typedef struct A_sent_ *A_sent;
typedef struct A_exp_ *A_exp;

/* Los tipos de operadores binarios válidos son: */

typedef enum {A_mas,A_menos,A_por,A_entre} A_opbin;

/*-----------------------------------------------------------------------
Los nodos de un árbol se definen polimórficamente. Están formados por:
- Un indicador de cuál es el tipo de nodo que estamos creando (dependiendo del 
  tipo  de sentencia)
- Una unión que contiene los campos correspondientes para esa instancia 
  particular que estamos creando 
  Así, por ejemplo, un nodo que almacene una sentencia de asignación debe 
  contener un A_sentComp en el campo clase, y debe utilizar el contenido de 
  campo asigna de la unión u; es decir debe contener una cadena (el 
  identificador) y un apuntador a una estructura de tipo exp (que contiene la 
  expresión).
---------------------------------------------------------------------------*/

struct A_sent_ {enum {A_sentComp, A_sentAsigna, A_sentDespl} clase;
             union {struct {A_sent sent1, sent2;} compuesta;       
                    struct {S_symbol id; A_exp exp;} asigna;
                    struct {A_exp exp;} despl;
                   } u;
            };
/*--------------------------------------------------------------------------- 
   Para crear cada uno de los nodos, deben existir los constructores
   correspondientes, uno para cada tipo de sentencia válida. Todo lo que hacen 
   es crear un nuevo nodo del tipo indicado, solicitando el espacio en memoria
   llenando los campos correspondientes. Cabe hacer notar que hay que tener 
   cuidado al invocarlos dado que tienen un nombre muy parecido al de los
   valores que puede tomar el campo clase de la estructura A_sent.
---------------------------------------------------------------------------*/
   
A_sent A_SentComp(A_sent sent1, A_sent sent2);
A_sent A_SentAsigna(S_symbol id, A_exp exp);
A_sent A_SentDespl(A_exp exp);

struct A_exp_ {enum {A_expId, A_expCad, A_expNum, A_expOp, A_expSec} clase;
             union {S_symbol id;
		    string cad;
                    int num;
                    struct {A_exp izq; A_opbin oper; A_exp der;} op;
                    struct {A_sent sent; A_exp exp;} esec;
                   } u;
            };

A_exp A_ExpId(S_symbol id);
A_exp A_ExpCad(string cad);
A_exp A_ExpNum(int num);
A_exp A_ExpOp(A_exp izq, A_opbin oper, A_exp der);
A_exp A_ExpSec(A_sent sent, A_exp exp);
#endif
