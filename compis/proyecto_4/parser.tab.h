/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DEF = 258,                     /* DEF  */
    INT_TYPE = 259,                /* INT_TYPE  */
    RETURN = 260,                  /* RETURN  */
    PRINT = 261,                   /* PRINT  */
    OPEN_PAREN = 262,              /* OPEN_PAREN  */
    CLOSE_PAREN = 263,             /* CLOSE_PAREN  */
    OPEN_BRACE = 264,              /* OPEN_BRACE  */
    CLOSE_BRACE = 265,             /* CLOSE_BRACE  */
    SEMICOLON = 266,               /* SEMICOLON  */
    ASSIGN = 267,                  /* ASSIGN  */
    COMMA = 268,                   /* COMMA  */
    IDENTIFIER = 269,              /* IDENTIFIER  */
    INTEGER_CONSTANT = 270,        /* INTEGER_CONSTANT  */
    PLUS = 271,                    /* PLUS  */
    MINUS = 272,                   /* MINUS  */
    MULTIPLY = 273,                /* MULTIPLY  */
    DIVIDE = 274,                  /* DIVIDE  */
    EQUALS = 275,                  /* EQUALS  */
    NOT_EQUALS = 276,              /* NOT_EQUALS  */
    GREATER = 277,                 /* GREATER  */
    GREATER_EQUAL = 278,           /* GREATER_EQUAL  */
    LESS = 279,                    /* LESS  */
    LESS_EQUAL = 280               /* LESS_EQUAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser.y"

    char *strval;
    int intval;
    // Otros tipos si es necesario

#line 95 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
