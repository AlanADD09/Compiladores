#ifndef Y_TAB_H
#define Y_TAB_H
typedef union {
   int pos;
   int ival;
   string sval;
} YYSTYPE;
#define	ID	258
#define	STRING	259
#define	INT	260
#define	DESPLIEGA 261
#define SI        262
#define OTRO      263
#define AND       264 
#define OR        265 
#define NOT       266 
#define DIFER     267 
#define IGUAL     268 
extern YYSTYPE yylval;
#endif
