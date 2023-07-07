/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_EXPR_YACC_H_INCLUDED
# define YY_YY_EXPR_YACC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BIN_STRCMP_TK = 258,
    BIN_NUMCMP_TK = 259,
    BIN_NUMEQ_TK = 260,
    BIN_NUMNEQ_TK = 261,
    BIN_NUMLT_TK = 262,
    BIN_NUMLE_TK = 263,
    BIN_NUMGT_TK = 264,
    BIN_NUMGE_TK = 265,
    BIN_NUMADD_TK = 266,
    BIN_NUMSUB_TK = 267,
    BIN_NUMMUL_TK = 268,
    BIN_NUMDIV_TK = 269,
    BIN_NUMMOD_TK = 270,
    BIN_NUMAND_TK = 271,
    BIN_NUMXOR_TK = 272,
    BIN_NUMOR_TK = 273,
    BIN_ROOT_TK = 274,
    UN_NUMSUP_TK = 275,
    UN_NUMINF_TK = 276,
    UN_NUMNOT_TK = 277,
    UN_STRNUM_TK = 278,
    UN_STRLEN_TK = 279,
    PAROP_TK = 280,
    PARCL_TK = 281,
    DOT_TK = 282,
    COMA_TK = 283,
    ID_TK = 284,
    VAL_STR_TK = 285,
    VAL_NUM_TK = 286
  };
#endif
/* Tokens.  */
#define BIN_STRCMP_TK 258
#define BIN_NUMCMP_TK 259
#define BIN_NUMEQ_TK 260
#define BIN_NUMNEQ_TK 261
#define BIN_NUMLT_TK 262
#define BIN_NUMLE_TK 263
#define BIN_NUMGT_TK 264
#define BIN_NUMGE_TK 265
#define BIN_NUMADD_TK 266
#define BIN_NUMSUB_TK 267
#define BIN_NUMMUL_TK 268
#define BIN_NUMDIV_TK 269
#define BIN_NUMMOD_TK 270
#define BIN_NUMAND_TK 271
#define BIN_NUMXOR_TK 272
#define BIN_NUMOR_TK 273
#define BIN_ROOT_TK 274
#define UN_NUMSUP_TK 275
#define UN_NUMINF_TK 276
#define UN_NUMNOT_TK 277
#define UN_STRNUM_TK 278
#define UN_STRLEN_TK 279
#define PAROP_TK 280
#define PARCL_TK 281
#define DOT_TK 282
#define COMA_TK 283
#define ID_TK 284
#define VAL_STR_TK 285
#define VAL_NUM_TK 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "//oio-sds/cluster/module/expr.yacc.y" /* yacc.c:1909  */

	double n;
	char* s;
	struct expr_s* e;

#line 122 "expr.yacc.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_EXPR_YACC_H_INCLUDED  */
