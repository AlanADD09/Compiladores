/* pretty.c */
#include "pretty.h"
#include "tree.h"
#include <stdio.h>

void prettyEXP(EXP *e){
	switch (e->kind){
	   case k_expressionKindIntLiteral:
	   	  printf("%d\n", e->val.intLiteral);
	   	  break;
	   case k_expressionKindAddition:
	      printf("(");
	      prettyEXP(e->val.binary.lhs);
	      printf("+");
	      prettyEXP(e->val.binary.rhs);
	      printf(")");
	      break;
	}
}
