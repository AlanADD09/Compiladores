#ifndef TREE_H
#define TREE_H
typedef enum{
   k_expressionKindIntLiteral,
   k_expressionKindAddition
//   k_expressionKindMultiplication
} ExpressionKind;
typedef struct EXP EXP;
struct EXP{
   ExpressionKind kind;
   union{
   	   char *identifier;
   	   int intLiteral;
   	   struct {EXP *lhs; EXP *rhs;} binary;
   } val;
};
EXP *makeEXP_intLiteral (int intLiteral);

#endif