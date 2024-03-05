#include "util.h"
#include "tree.h"

EXP *makeEXP_intLiteral(int intLiteral){

	EXP *e=checked_malloc(sizeof(EXP));
	e->kind = k_expressionKindIntLiteral;
    e->val.intLiteral = intLiteral;
    return e;
}