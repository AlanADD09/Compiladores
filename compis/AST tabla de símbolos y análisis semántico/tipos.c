#include "tipos.h"

S_tyList S_TyList(S_ty t, S_tyList l){
   S_tyList lista=(S_tyList)checked_malloc(sizeof (S_tyList));
   lista->t = t;
   lista->l = l;
   return lista;
}

S_asoc S_Asoc(S_ambiente a,S_ty t,S_tyList largs,unsigned despl){
   S_asoc asociacion=(S_asoc)checked_malloc(sizeof (struct S_asoc_));
   asociacion->a = a;
   asociacion->t = t;
   asociacion->largs = largs;
   asociacion->despl = despl;
   return asociacion;
}

