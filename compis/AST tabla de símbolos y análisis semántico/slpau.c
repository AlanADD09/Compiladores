#include "util.h"
#include "slpau.h"

A_sent A_SentComp(A_sent sent1, A_sent sent2){
  A_sent s = checked_malloc(sizeof *s);
  s->clase=A_sentComp; s->u.compuesta.sent1=sent1; s->u.compuesta.sent2=sent2;
  return s;
}

A_sent A_SentAsigna(S_symbol id, A_exp exp) {
  A_sent s = checked_malloc(sizeof *s);
  s->clase=A_sentAsigna; s->u.asigna.id=id; s->u.asigna.exp=exp;
  return s;
}

A_sent A_SentDespl(A_exp exp) {
  A_sent s = checked_malloc(sizeof *s);
  s->clase=A_sentDespl; s->u.despl.exp=exp;
  return s;
}

A_exp A_ExpId(S_symbol id) {
  A_exp e = checked_malloc(sizeof *e);
  e->clase=A_expId; e->u.id=id;
  return e;
}

A_exp A_ExpCad(string cad) {
  A_exp e = checked_malloc(sizeof *e);
  e->clase=A_expId; e->u.cad=cad;
  return e;
}

A_exp A_ExpNum(int num) {
  A_exp e = checked_malloc(sizeof *e);
  e->clase=A_expNum; e->u.num=num;
  return e;
}

A_exp A_ExpOp(A_exp izq, A_opbin oper, A_exp der) {
  A_exp e = checked_malloc(sizeof *e);
  e->clase=A_expOp; e->u.op.izq=izq; e->u.op.oper=oper; e->u.op.der=der;
  return e;
}

A_exp A_ExpSec(A_sent sent, A_exp exp) {
  A_exp e = checked_malloc(sizeof *e);
  e->clase=A_expSec; e->u.esec.sent=sent; e->u.esec.exp=exp;
  return e;
}
