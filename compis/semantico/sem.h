#ifndef SEM_H
#define SEM_H

#include "tipos.h"
#include "slpau.h"

typedef enum{S_exito, S_error} S_califica;

/* Un resultado de an�lisis sem�ntico: */
typedef struct S_resultado_ *S_resultado;

struct S_resultado_{
  S_califica c;      /* �Tuvo �xito el an�lisis?           */
  S_ty t;            /* El tipo asociado al nodo analizado */
  char *codigo_gen;  /* El c�digo ensamblador generado     */
};

S_resultado S_Resultado(S_califica c,S_ty t,char *codigo_gen);

S_resultado trad_Sent(A_sent s);
S_resultado trad_Exp(A_exp e);

#endif
