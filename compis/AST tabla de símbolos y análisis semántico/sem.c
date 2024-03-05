/* Analisis Semántico para el lenguaje simple */
#include <stdio.h>
#include "sem.h"
#include "slpau.h"
#include "errormsg.h"
#include "symbol.h"
#include "tipos.h"
#include "util.h"

extern S_table tvar;
int despl= 0; /* Lo usaremos para calcular el desplazamiento de un ID en       
                 la pila */

S_resultado S_Resultado(S_califica c,S_ty t,char *codigo_gen){
   S_resultado resultado=checked_malloc(sizeof (struct S_resultado_));
   resultado->c = c;
   resultado->t = t;
   resultado->codigo_gen = codigo_gen;
   return resultado;
}

S_resultado trad_Sent(A_sent s);
S_resultado trad_Exp(A_exp e);


/* Realizamos el análisis semántico de una sentencia */

S_resultado trad_Sent(A_sent s){
  S_resultado r_izq,r_der,r;
  S_asoc asoc;

//  assert(s); /* La sentencia no debe ser nula.*/

  if(!s)
    return NULL;
  assert(tvar);  /* Tampoco la tabla de símbolos */

  switch (s->clase){
    case A_sentComp: /* Sentencia compuesta, sólo es un puente,
			   el resultado depende de las 2 sentencias
			   que contiene este nodo */
      printf("Iniciando sentencia compuesta\n");

      r_izq = trad_Sent(s->u.compuesta.sent1);
      r_der = trad_Sent(s->u.compuesta.sent2);
      if(r_izq->c==S_exito && r_der->c==S_exito)
	 r=S_Resultado(S_exito,T_void,NULL);
      else
	 r=S_Resultado(S_error,T_void,NULL);
         printf("Finalizando sentencia compuesta\n");
      return r;
    case A_sentAsigna:  /* Sentencia de asignación: El ID del lado izquierdo
			  debe estar ya definido y la expresión por asignar
			  debe ser del mismo tipo que el ID */
      printf("Revisando asignacion %s \n",S_name(s->u.asigna.id));
      r_der = trad_Exp(s->u.asigna.exp);
      if(r_der->c==S_exito){
	asoc = S_look(tvar,s->u.asigna.id);
	//      printf("Ya pasamos la busqueda de  %s \n",S_name(s->u.assign.id));
	if(!asoc){
	  printf("Error:Variable %s no declarada\n",S_name(s->u.asigna.id));
	  r=S_Resultado(S_error,T_void,NULL);
	  //return r;
	}
	else if(asoc->t !=r_der->t){
	  printf("Error:La expresión en la asignación no coincide con el tipo \
                  definido para el id %s \n", S_name(s->u.asigna.id));
	  r=S_Resultado(S_error,T_void,NULL);
	  //return r;
	}
	else r=S_Resultado(S_exito,T_void,NULL);
	return r;
      }
      else{
	r = S_Resultado(S_error,T_void,NULL);
        return r;       
      }
    case A_sentDespl: /* Sentencia de impresión: Todo lo que hay que hacer */
		      /* es invocar a la función de análisis de una lista */
		      /* de expresiones */
      r_izq = tradExp(s->u.despl.exp);
      if(r_izq->c==S_exito)
	 r = S_Resultado(S_exito,T_void,NULL);
      else
	r = S_Resultado(S_error,T_void,NULL);
      return r;
    default: /* Esto no deber¡a ocurrir: Tipo desconocido */
       r=S_Resultado(S_error,T_void,NULL);
       return;
  }
}

S_resultado trad_Exp(A_exp e){
  S_resultado r_izq,r_der,r;
  S_asoc asoc;
  /*assert(e); */
//  assert(tvar);
  switch (e->clase){
    case A_expId: /* Expresión de ID, debe estar ya definido en la tabla de
		     símbolos. El tipo asociado es el que notificamos hacia
		     arriba. En el caso de ulp, aquí deberás revisar además
		     que el ID no esté definido como una función.*/
      asoc = S_look(tvar,e->u.id);
      if(!asoc){
	printf("Error:Variable %s no declarada\n",S_name(e->u.id));
	r=S_Resultado(S_error,T_void,NULL);
      }
      else
	r=S_Resultado(S_exito,asoc->t,NULL);
      return r;
    case A_expCad: /* Una cadena, no hay mucho que hacer... */
        printf("Encontre una cadena  %s \n",e->u.cad);
	r=S_Resultado(S_exito,T_string,NULL);
	return r;
    case A_expNum: /* Un entero... */
	r=S_Resultado(S_exito,T_int,NULL);
	return r;
    case A_expOp: /* Una expresión de operadores:
		     -Si alguno de los 2 operandos no es entero, ERROR
		     -Se podría incluso revisar, para el caso de la división
		      que el divisor no sea el numeral 0 */
      r_izq = trad_Exp(e->u.op.izq);
      r_der = trad_Exp(e->u.op.der);

      if(r_izq->c!=S_exito || r_der->c!=S_exito){
	r=S_Resultado(S_error,T_void,NULL);
	return r;
      }

      if(r_izq->t!=T_int || r_der->t!=T_int){
	printf("Expresion de tipo no entero en operación aritmética\n");
	r=S_Resultado(S_error,T_int,NULL);
	return r;
      }
      r=S_Resultado(S_exito,T_int,NULL);
      return r;
    case A_expSec: /* Expresión con sentencia. Esto define un nuevo ambiente
		       local en simple, muy semejante e una función --excepto
		       que no tiene argumentos ni nombre */
      S_beginScope(tvar);
      r_izq = trad_Sent(e->u.esec.sent);
      if(r_izq->c!=S_exito){
	r=S_Resultado(S_error,T_void,NULL);
        S_endScope(tvar);
	return r;
      }
      r_der = trad_Exp(e->u.esec.exp);
      if(r_der->c!=S_exito){
	r=S_Resultado(S_error,T_void,NULL);
        S_endScope(tvar);
	return r;
      }
      r=S_Resultado(S_exito,r->t,NULL);
      return r;
      S_endScope(tvar);
    default:             /* Esto no deber¡a ocurrir: Tipo desconocido */
       r=S_Resultado(S_error,T_void,NULL);
       return;
  }
}

