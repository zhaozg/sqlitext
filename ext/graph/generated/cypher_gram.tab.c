/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 1



/* Substitute the type names.  */
#define YYSTYPE CYPHER_YYSTYPE
#define YYLTYPE CYPHER_YYLTYPE
/* Substitute the variable and function names.  */
#define yyparse cypher_yyparse
#define yylex   cypher_yylex
#define yyerror cypher_yyerror
#define yydebug cypher_yydebug

/* First part of user prologue.  */
#line 1 "src/backend/parser/cypher_gram.y"

/*
 * Cypher Grammar for GraphQLite
 * Simplified version based on Apache AGE grammar for SQLite compatibility
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser/cypher_ast.h"
#include "parser/cypher_parser.h"

/* Forward declarations */
void cypher_yyerror(CYPHER_YYLTYPE *yylloc, cypher_parser_context *context, const char *msg);
int cypher_yylex(CYPHER_YYSTYPE *yylval, CYPHER_YYLTYPE *yylloc, cypher_parser_context *context);


#line 83 "build/parser/cypher_gram.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "cypher_gram.tab.h"

/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_DECIMAL = 4,                    /* DECIMAL  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_IDENTIFIER = 6,                 /* IDENTIFIER  */
  YYSYMBOL_PARAMETER = 7,                  /* PARAMETER  */
  YYSYMBOL_BQIDENT = 8,                    /* BQIDENT  */
  YYSYMBOL_NOT_EQ = 9,                     /* NOT_EQ  */
  YYSYMBOL_LT_EQ = 10,                     /* LT_EQ  */
  YYSYMBOL_GT_EQ = 11,                     /* GT_EQ  */
  YYSYMBOL_DOT_DOT = 12,                   /* DOT_DOT  */
  YYSYMBOL_TYPECAST = 13,                  /* TYPECAST  */
  YYSYMBOL_PLUS_EQ = 14,                   /* PLUS_EQ  */
  YYSYMBOL_REGEX_MATCH = 15,               /* REGEX_MATCH  */
  YYSYMBOL_MATCH = 16,                     /* MATCH  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_CREATE = 18,                    /* CREATE  */
  YYSYMBOL_WHERE = 19,                     /* WHERE  */
  YYSYMBOL_WITH = 20,                      /* WITH  */
  YYSYMBOL_SET = 21,                       /* SET  */
  YYSYMBOL_DELETE = 22,                    /* DELETE  */
  YYSYMBOL_REMOVE = 23,                    /* REMOVE  */
  YYSYMBOL_MERGE = 24,                     /* MERGE  */
  YYSYMBOL_UNWIND = 25,                    /* UNWIND  */
  YYSYMBOL_DETACH = 26,                    /* DETACH  */
  YYSYMBOL_FOREACH = 27,                   /* FOREACH  */
  YYSYMBOL_CALL = 28,                      /* CALL  */
  YYSYMBOL_OPTIONAL = 29,                  /* OPTIONAL  */
  YYSYMBOL_DISTINCT = 30,                  /* DISTINCT  */
  YYSYMBOL_ORDER = 31,                     /* ORDER  */
  YYSYMBOL_BY = 32,                        /* BY  */
  YYSYMBOL_SKIP = 33,                      /* SKIP  */
  YYSYMBOL_LIMIT = 34,                     /* LIMIT  */
  YYSYMBOL_AS = 35,                        /* AS  */
  YYSYMBOL_ASC = 36,                       /* ASC  */
  YYSYMBOL_DESC = 37,                      /* DESC  */
  YYSYMBOL_AND = 38,                       /* AND  */
  YYSYMBOL_OR = 39,                        /* OR  */
  YYSYMBOL_XOR = 40,                       /* XOR  */
  YYSYMBOL_NOT = 41,                       /* NOT  */
  YYSYMBOL_IN = 42,                        /* IN  */
  YYSYMBOL_IS = 43,                        /* IS  */
  YYSYMBOL_NULL_P = 44,                    /* NULL_P  */
  YYSYMBOL_TRUE_P = 45,                    /* TRUE_P  */
  YYSYMBOL_FALSE_P = 46,                   /* FALSE_P  */
  YYSYMBOL_EXISTS = 47,                    /* EXISTS  */
  YYSYMBOL_ANY = 48,                       /* ANY  */
  YYSYMBOL_NONE = 49,                      /* NONE  */
  YYSYMBOL_SINGLE = 50,                    /* SINGLE  */
  YYSYMBOL_REDUCE = 51,                    /* REDUCE  */
  YYSYMBOL_UNION = 52,                     /* UNION  */
  YYSYMBOL_ALL = 53,                       /* ALL  */
  YYSYMBOL_CASE = 54,                      /* CASE  */
  YYSYMBOL_WHEN = 55,                      /* WHEN  */
  YYSYMBOL_THEN = 56,                      /* THEN  */
  YYSYMBOL_ELSE = 57,                      /* ELSE  */
  YYSYMBOL_END_P = 58,                     /* END_P  */
  YYSYMBOL_ON = 59,                        /* ON  */
  YYSYMBOL_SHORTESTPATH = 60,              /* SHORTESTPATH  */
  YYSYMBOL_ALLSHORTESTPATHS = 61,          /* ALLSHORTESTPATHS  */
  YYSYMBOL_PATTERN = 62,                   /* PATTERN  */
  YYSYMBOL_EXPLAIN = 63,                   /* EXPLAIN  */
  YYSYMBOL_LOAD = 64,                      /* LOAD  */
  YYSYMBOL_CSV = 65,                       /* CSV  */
  YYSYMBOL_FROM = 66,                      /* FROM  */
  YYSYMBOL_HEADERS = 67,                   /* HEADERS  */
  YYSYMBOL_FIELDTERMINATOR = 68,           /* FIELDTERMINATOR  */
  YYSYMBOL_STARTS = 69,                    /* STARTS  */
  YYSYMBOL_ENDS = 70,                      /* ENDS  */
  YYSYMBOL_CONTAINS = 71,                  /* CONTAINS  */
  YYSYMBOL_72_ = 72,                       /* '='  */
  YYSYMBOL_73_ = 73,                       /* '<'  */
  YYSYMBOL_74_ = 74,                       /* '>'  */
  YYSYMBOL_75_ = 75,                       /* '+'  */
  YYSYMBOL_76_ = 76,                       /* '-'  */
  YYSYMBOL_77_ = 77,                       /* '*'  */
  YYSYMBOL_78_ = 78,                       /* '/'  */
  YYSYMBOL_79_ = 79,                       /* '%'  */
  YYSYMBOL_80_ = 80,                       /* '^'  */
  YYSYMBOL_81_ = 81,                       /* '.'  */
  YYSYMBOL_82_ = 82,                       /* '['  */
  YYSYMBOL_UNARY_MINUS = 83,               /* UNARY_MINUS  */
  YYSYMBOL_UNARY_PLUS = 84,                /* UNARY_PLUS  */
  YYSYMBOL_85_ = 85,                       /* ';'  */
  YYSYMBOL_86_ = 86,                       /* '('  */
  YYSYMBOL_87_ = 87,                       /* '|'  */
  YYSYMBOL_88_ = 88,                       /* ')'  */
  YYSYMBOL_89_ = 89,                       /* '{'  */
  YYSYMBOL_90_ = 90,                       /* '}'  */
  YYSYMBOL_91_ = 91,                       /* ','  */
  YYSYMBOL_92_ = 92,                       /* ':'  */
  YYSYMBOL_93_ = 93,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 94,                  /* $accept  */
  YYSYMBOL_stmt = 95,                      /* stmt  */
  YYSYMBOL_union_query = 96,               /* union_query  */
  YYSYMBOL_single_query = 97,              /* single_query  */
  YYSYMBOL_clause_list = 98,               /* clause_list  */
  YYSYMBOL_clause = 99,                    /* clause  */
  YYSYMBOL_match_clause = 100,             /* match_clause  */
  YYSYMBOL_from_graph_opt = 101,           /* from_graph_opt  */
  YYSYMBOL_optional_opt = 102,             /* optional_opt  */
  YYSYMBOL_return_clause = 103,            /* return_clause  */
  YYSYMBOL_with_clause = 104,              /* with_clause  */
  YYSYMBOL_unwind_clause = 105,            /* unwind_clause  */
  YYSYMBOL_foreach_clause = 106,           /* foreach_clause  */
  YYSYMBOL_call_clause = 107,              /* call_clause  */
  YYSYMBOL_load_csv_clause = 108,          /* load_csv_clause  */
  YYSYMBOL_foreach_update_list = 109,      /* foreach_update_list  */
  YYSYMBOL_distinct_opt = 110,             /* distinct_opt  */
  YYSYMBOL_order_by_opt = 111,             /* order_by_opt  */
  YYSYMBOL_skip_opt = 112,                 /* skip_opt  */
  YYSYMBOL_limit_opt = 113,                /* limit_opt  */
  YYSYMBOL_where_opt = 114,                /* where_opt  */
  YYSYMBOL_order_by_list = 115,            /* order_by_list  */
  YYSYMBOL_order_by_item = 116,            /* order_by_item  */
  YYSYMBOL_return_item_list = 117,         /* return_item_list  */
  YYSYMBOL_return_item = 118,              /* return_item  */
  YYSYMBOL_set_item_list = 119,            /* set_item_list  */
  YYSYMBOL_set_item = 120,                 /* set_item  */
  YYSYMBOL_create_clause = 121,            /* create_clause  */
  YYSYMBOL_merge_clause = 122,             /* merge_clause  */
  YYSYMBOL_on_create_clause = 123,         /* on_create_clause  */
  YYSYMBOL_on_match_clause = 124,          /* on_match_clause  */
  YYSYMBOL_set_clause = 125,               /* set_clause  */
  YYSYMBOL_delete_clause = 126,            /* delete_clause  */
  YYSYMBOL_delete_item_list = 127,         /* delete_item_list  */
  YYSYMBOL_delete_item = 128,              /* delete_item  */
  YYSYMBOL_remove_clause = 129,            /* remove_clause  */
  YYSYMBOL_remove_item_list = 130,         /* remove_item_list  */
  YYSYMBOL_remove_item = 131,              /* remove_item  */
  YYSYMBOL_detach_opt = 132,               /* detach_opt  */
  YYSYMBOL_pattern_list = 133,             /* pattern_list  */
  YYSYMBOL_simple_path = 134,              /* simple_path  */
  YYSYMBOL_path = 135,                     /* path  */
  YYSYMBOL_node_pattern = 136,             /* node_pattern  */
  YYSYMBOL_rel_pattern = 137,              /* rel_pattern  */
  YYSYMBOL_variable_opt = 138,             /* variable_opt  */
  YYSYMBOL_varlen_range_opt = 139,         /* varlen_range_opt  */
  YYSYMBOL_label_opt = 140,                /* label_opt  */
  YYSYMBOL_label_list = 141,               /* label_list  */
  YYSYMBOL_rel_type_list = 142,            /* rel_type_list  */
  YYSYMBOL_expr = 143,                     /* expr  */
  YYSYMBOL_primary_expr = 144,             /* primary_expr  */
  YYSYMBOL_literal_expr = 145,             /* literal_expr  */
  YYSYMBOL_function_call = 146,            /* function_call  */
  YYSYMBOL_list_predicate = 147,           /* list_predicate  */
  YYSYMBOL_reduce_expr = 148,              /* reduce_expr  */
  YYSYMBOL_argument_list = 149,            /* argument_list  */
  YYSYMBOL_list_literal = 150,             /* list_literal  */
  YYSYMBOL_list_comprehension = 151,       /* list_comprehension  */
  YYSYMBOL_pattern_comprehension = 152,    /* pattern_comprehension  */
  YYSYMBOL_map_literal = 153,              /* map_literal  */
  YYSYMBOL_map_projection = 154,           /* map_projection  */
  YYSYMBOL_map_projection_list = 155,      /* map_projection_list  */
  YYSYMBOL_map_projection_item = 156,      /* map_projection_item  */
  YYSYMBOL_case_expression = 157,          /* case_expression  */
  YYSYMBOL_when_clause_list = 158,         /* when_clause_list  */
  YYSYMBOL_when_clause = 159,              /* when_clause  */
  YYSYMBOL_literal = 160,                  /* literal  */
  YYSYMBOL_identifier = 161,               /* identifier  */
  YYSYMBOL_parameter = 162,                /* parameter  */
  YYSYMBOL_properties_opt = 163,           /* properties_opt  */
  YYSYMBOL_map_pair_list = 164,            /* map_pair_list  */
  YYSYMBOL_map_pair = 165                  /* map_pair  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;
static YYLTYPE yyloc_default
# if defined CYPHER_YYLTYPE_IS_TRIVIAL && CYPHER_YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;



#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif
#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#ifdef __cplusplus
  typedef bool yybool;
# define yytrue true
# define yyfalse false
#else
  /* When we move to stdbool, get rid of the various casts to yybool.  */
  typedef signed char yybool;
# define yytrue 1
# define yyfalse 0
#endif

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify Clang and ICC.  */
# define YYLONGJMP(Env, Val)                    \
 do {                                           \
   longjmp (Env, Val);                          \
   YY_ASSERT (0);                               \
 } while (yyfalse)
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* The _Noreturn keyword of C11.  */
#ifndef _Noreturn
# if (defined __cplusplus \
      && ((201103 <= __cplusplus && !(__GNUC__ == 4 && __GNUC_MINOR__ == 7)) \
          || (defined _MSC_VER && 1900 <= _MSC_VER)))
#  define _Noreturn [[noreturn]]
# elif ((!defined __cplusplus || defined __clang__) \
        && (201112 <= (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) \
            || (!defined __STRICT_ANSI__ \
                && (4 < __GNUC__ + (7 <= __GNUC_MINOR__) \
                    || (defined __apple_build_version__ \
                        ? 6000000 <= __apple_build_version__ \
                        : 3 < __clang_major__ + (5 <= __clang_minor__))))))
   /* _Noreturn works as-is.  */
# elif (2 < __GNUC__ + (8 <= __GNUC_MINOR__) || defined __clang__ \
        || 0x5110 <= __SUNPRO_C)
#  define _Noreturn __attribute__ ((__noreturn__))
# elif 1200 <= (defined _MSC_VER ? _MSC_VER : 0)
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  102
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2679

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  263
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  573
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 13
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    79,     2,     2,
      86,    88,    77,    75,    91,    76,    81,    78,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    92,    85,
      73,    72,    74,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    82,     2,    93,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    89,    87,    90,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    83,    84
};

#if CYPHER_YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   166,   166,   171,   176,   185,   196,   200,   204,   211,
     218,   223,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   247,   254,   255,   262,   263,   268,
     272,   277,   285,   289,   298,   307,   320,   330,   336,   342,
     349,   360,   365,   370,   375,   380,   385,   390,   395,   400,
     405,   410,   415,   423,   424,   428,   429,   433,   434,   438,
     439,   443,   444,   448,   453,   461,   462,   463,   468,   473,
     481,   485,   493,   498,   506,   510,   515,   528,   536,   540,
     544,   548,   552,   559,   566,   574,   582,   589,   594,   602,
     611,   618,   623,   631,   640,   649,   658,   667,   679,   684,
     691,   696,   705,   711,   730,   734,   740,   747,   752,   759,
     767,   782,   786,   791,   796,   803,   807,   812,   817,   824,
     828,   833,   838,   845,   849,   853,   860,   861,   862,   863,
     869,   870,   872,   874,   876,   878,   883,   884,   889,   896,
     903,   910,   920,   930,   941,   951,   962,   972,   983,   993,
    1004,  1011,  1018,  1025,  1036,  1037,  1038,  1057,  1058,  1059,
    1060,  1061,  1062,  1063,  1064,  1065,  1066,  1067,  1068,  1069,
    1070,  1071,  1072,  1073,  1074,  1075,  1076,  1077,  1078,  1079,
    1085,  1098,  1112,  1117,  1122,  1126,  1130,  1134,  1141,  1142,
    1143,  1144,  1145,  1146,  1147,  1148,  1149,  1150,  1151,  1152,
    1153,  1163,  1167,  1182,  1208,  1215,  1223,  1228,  1238,  1242,
    1247,  1256,  1261,  1266,  1271,  1280,  1291,  1296,  1305,  1309,
    1326,  1331,  1336,  1341,  1358,  1371,  1388,  1392,  1400,  1409,
    1414,  1422,  1428,  1433,  1440,  1454,  1458,  1463,  1467,  1474,
    1479,  1487,  1494,  1498,  1502,  1507,  1511,  1515,  1522,  1527,
    1532,  1540,  1549,  1550,  1551,  1558,  1563,  1571,  1575,  1579,
    1583,  1587,  1591,  1595
};
#endif

#define YYPACT_NINF (-399)
#define YYTABLE_NINF (-163)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     412,    15,    18,    30,   733,   241,    18,   789,  -399,   -57,
     -46,  -399,   557,   -14,    69,   -20,  -399,   310,  -399,  -399,
      58,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,   102,   115,    51,   789,   150,   167,   206,   148,
     192,   -26,  -399,  -399,  -399,    51,   789,  -399,  -399,  -399,
     213,  -399,  -399,   789,  -399,  -399,  -399,   232,   243,   287,
     294,   304,   321,   565,  -399,   345,   362,   367,   789,   789,
     317,   845,    36,   309,  -399,   -26,  1924,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,   103,   382,   381,  -399,   -25,   225,  1969,   474,   557,
      60,     5,  -399,   391,  -399,  -399,    18,   482,    51,   461,
     477,     0,  -399,  2014,   129,   418,   418,  -399,  -399,  -399,
     428,    18,   454,   147,   418,   477,     0,   478,     7,   527,
    2597,    24,   528,   529,   533,   534,   535,   789,  2059,   302,
    -399,   789,   789,   789,  -399,  -399,    -9,   901,  -399,   170,
     290,   176,   252,  1406,   452,   453,   458,   460,   464,   465,
     466,  -399,   421,  -399,   733,   418,   789,   789,   789,   789,
     789,   789,   789,   789,   789,   177,   526,   539,   789,   789,
     789,   789,   789,   789,   789,   789,   789,   267,   621,   441,
     556,   450,   241,   444,   504,   506,   570,   581,   789,   546,
     -31,  -399,   522,   585,   557,  -399,    89,  -399,   500,  -399,
     477,   789,   789,   558,   789,   477,   587,   508,   509,   -26,
     120,   125,   451,   507,   505,  -399,   166,   524,   148,  -399,
     558,   477,   789,   511,  -399,  2469,   281,   510,     4,   425,
    -399,   210,   122,   306,   559,   561,   562,   536,   563,  2106,
     326,   789,  -399,  -399,   307,   313,   314,   789,   428,  -399,
    -399,   789,   789,   789,   789,   789,   789,   789,  -399,   235,
    -399,   369,   203,   203,   203,  2469,   203,  2597,  2514,  2556,
     222,   573,  -399,   789,   789,   203,  2154,   203,   203,   209,
     209,    -6,    -6,    -6,  -399,  -399,   789,  1000,  -399,  -399,
    -399,  -399,  -399,  -399,   579,   586,   606,  -399,   612,  -399,
    -399,  -399,   203,   789,  -399,   566,   596,  -399,   631,   619,
     482,   558,   548,  -399,  1879,  2469,   789,  -399,  -399,   558,
    -399,   418,   418,  -399,  -399,  -399,  -399,   180,   554,   471,
    -399,   148,  -399,    19,   619,   558,  1453,  -399,  -399,   789,
     677,  -399,  -399,  -399,     7,   637,  -399,   789,   789,   789,
     789,   789,   789,   789,  -399,  2199,  -399,  -399,  -399,   954,
     507,  2469,  2469,  2469,  2469,  2469,  2469,  2469,  -399,   418,
    -399,   203,   203,  1091,   420,  -399,   733,   733,  1735,   639,
     640,  -399,   789,  -399,  -399,  -399,   789,  -399,  -399,  2469,
    -399,   220,   221,  -399,   427,  -399,  -399,  -399,   110,   197,
     486,   507,  -399,   619,  -399,  2469,   642,  2469,  -399,   564,
    2244,  2289,  2334,  1361,  2379,  2469,  2424,  -399,   789,   789,
    -399,   567,  -399,  -399,  -399,  1136,   309,   309,   289,   610,
     582,  2469,  -399,  -399,  -399,  -399,   491,   507,   641,   646,
     -39,    70,   137,   568,  -399,  -399,  -399,   789,   789,   789,
     650,   789,  -399,  1045,  1181,   370,  -399,  -399,    31,  -399,
    -399,  -399,  -399,  -399,   651,   653,   -39,    70,   137,   571,
     656,  -399,     9,   507,    10,   507,    14,   507,   584,  1500,
    1547,  1594,   634,  1641,   789,  -399,  -399,   418,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,   595,  -399,   507,   507,   507,
     597,  -399,  -399,  -399,   492,   593,  -399,  -399,   495,   594,
    -399,  -399,   499,   600,   603,  -399,  -399,  -399,   789,  -399,
    1226,    16,   673,   601,   602,   605,  -399,  -399,  -399,   613,
    -399,  -399,   623,  -399,  -399,   624,  -399,  1781,  -399,   789,
     789,  -399,   625,   626,   628,   614,   632,   635,   789,  1827,
    1271,  -399,  -399,  -399,  -399,  -399,  -399,  1688,   789,  -399,
    -399,  1316,  -399
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
      27,    53,     0,    53,     0,     0,     0,     0,    98,     0,
       0,    28,    27,     0,     0,     2,     6,     9,    10,    12,
       0,    13,    14,    15,    16,    23,    17,    18,    19,    20,
      21,    22,     0,    54,    55,     0,     0,     0,     0,   126,
      77,   104,   100,   102,    54,    55,     0,   242,   243,   244,
     248,   251,   249,     0,   247,   245,   246,     0,     0,     0,
       0,     0,     0,     0,   250,     0,     0,     0,     0,     0,
       0,   126,     0,    85,    72,     0,     0,   154,   188,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   201,   189,
     190,     0,     0,    90,    91,    78,   248,     0,     0,    27,
       4,     0,     1,    27,     3,    11,     0,     0,    55,     0,
      57,    55,    68,    70,     0,     0,     0,   127,   128,   129,
     136,     0,     0,     0,     0,    57,    55,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     239,     0,     0,     0,   155,   156,   248,   126,   218,     0,
     248,   249,   250,     0,     0,     0,     0,     0,     0,     0,
       0,   226,     0,   255,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    79,    80,     0,     0,     0,     0,
       0,     5,     0,     0,    27,     7,    25,    89,    86,    87,
      57,     0,     0,    59,     0,    57,     0,     0,     0,   105,
       0,     0,     0,   252,   137,   101,     0,   125,   126,   103,
      59,    57,     0,     0,   202,   216,     0,     0,     0,     0,
     229,   200,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   235,   240,     0,     0,     0,     0,   136,   219,
     179,     0,     0,     0,     0,     0,     0,     0,   227,     0,
      73,   180,   163,   166,   167,    75,   168,   169,   170,   171,
     172,     0,   177,     0,     0,   175,    74,   164,   165,   157,
     158,   159,   160,   161,   182,   183,     0,     0,    93,    94,
      97,    95,    96,    92,     0,     0,     0,    81,     0,    82,
     200,    34,   162,     0,    36,     0,     0,     8,     0,    61,
       0,    59,    56,    63,    65,    58,     0,    30,    69,    59,
      71,     0,     0,   107,   109,   138,   139,     0,     0,     0,
     124,   126,   123,   130,    61,    59,     0,   205,   203,     0,
       0,   231,   232,   228,     0,     0,   206,     0,     0,     0,
       0,     0,     0,     0,   237,     0,   209,   210,   208,     0,
     252,   259,   257,   258,   262,   263,   260,   261,   256,     0,
     178,   173,   174,     0,     0,   184,     0,     0,     0,     0,
       0,    26,     0,    24,    88,    31,     0,    66,    67,    60,
      29,     0,     0,   253,     0,   110,   140,   141,   130,   131,
       0,   252,    33,    61,   204,   217,     0,   234,   230,     0,
       0,     0,     0,     0,     0,   241,     0,   236,     0,     0,
     220,     0,   181,   187,   186,     0,    84,    83,    99,     0,
      37,    62,    64,   106,   108,   254,     0,   252,   132,     0,
     130,   130,   130,     0,    32,   233,   207,     0,     0,     0,
       0,     0,   238,     0,     0,     0,   185,    46,    99,    41,
      44,    42,    43,    45,     0,     0,   130,   130,   130,     0,
     134,   135,     0,   252,     0,   252,     0,   252,     0,     0,
       0,     0,     0,     0,     0,   221,   222,     0,    35,    52,
      47,    50,    48,    49,    51,    38,    39,   252,   252,   252,
       0,   133,   142,   144,     0,     0,   146,   148,     0,     0,
     150,   151,     0,     0,   119,   212,   213,   214,     0,   211,
       0,     0,     0,     0,     0,     0,   115,   143,   145,     0,
     147,   149,     0,   152,   153,     0,   111,     0,   223,     0,
       0,    40,     0,     0,     0,   120,   121,   122,     0,     0,
       0,   116,   117,   118,   112,   113,   114,     0,     0,   224,
     215,     0,   225
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -399,  -399,    -1,   -95,  -399,   688,  -399,  -399,  -399,  -399,
    -399,  -399,  -398,  -399,  -399,  -399,   705,   -18,  -116,  -224,
    -318,  -399,   315,    67,   498,   151,   549,  -351,  -322,   519,
     521,  -316,  -310,  -399,   396,  -285,  -399,   525,  -399,     8,
    -112,   598,    17,   -74,  -142,  -308,   462,  -399,   283,    -7,
    -399,  -399,  -399,  -399,  -399,   204,  -399,  -399,  -399,  -399,
    -399,  -399,   378,  -399,   604,  -132,  -399,  -399,  -399,  -358,
     397,   475
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    14,    15,    16,    17,    18,    19,   319,    20,    21,
      22,    23,    24,    25,    26,   468,    35,   110,   213,   327,
     393,   322,   323,   111,   112,    73,    74,    27,    28,   194,
     195,    29,    30,   208,   209,    31,    93,    94,    32,    40,
      41,    42,    75,   124,   120,   411,   223,   224,   452,    76,
      77,    78,    79,    80,    81,   236,    82,    83,    84,    85,
      86,   239,   240,    87,   139,   140,    88,    89,    90,   338,
     162,   163
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      97,   165,   219,   220,   221,   258,   344,   253,   205,   230,
     351,   100,   431,   237,    95,   512,   516,   513,   517,    43,
     520,   103,   521,    43,    36,   202,   412,   125,   113,    98,
     242,   109,   103,   257,   193,   549,   174,   175,   409,   113,
     467,   154,   155,    99,   156,    33,   130,   122,   482,     2,
     123,   101,     4,   453,     5,     6,   138,     8,     9,   314,
      44,   144,   145,   113,   153,   104,   121,   157,   158,   102,
     499,   203,   159,   160,   106,   187,   188,   127,    37,    38,
     128,   352,   109,   196,    37,    38,   343,   469,   238,   479,
     210,   214,    34,   215,   321,   454,   409,   395,   200,   329,
     447,   514,   518,   550,    39,   400,   522,    45,   231,   317,
      39,   410,   103,   126,   206,   345,   470,   500,   253,   498,
     235,   413,   471,    43,   107,   515,   161,   519,   472,   523,
     249,    43,    43,    43,   235,   235,   235,   149,    43,   243,
     153,   229,   483,   485,   487,   201,   501,   409,    43,   533,
     534,   535,   502,   473,   117,   318,   118,   484,   503,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   507,   508,
     509,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     121,   297,   271,   504,   189,   154,   155,   409,   156,   217,
     218,   312,   108,   122,   114,   190,   123,   379,   122,   408,
     448,   123,   446,   355,   324,   325,   119,   113,   333,   449,
     -76,   157,   158,   334,   409,    39,   159,   160,   281,   401,
     402,   282,   114,   227,   486,   346,   -76,   -76,   -76,   228,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     154,   155,   340,   156,   365,   174,   175,    91,   341,    92,
     369,   174,   175,   115,   371,   372,   373,   374,   375,   376,
     377,   214,   -76,   259,  -128,  -128,   157,   158,  -128,   -76,
     403,   159,   160,   294,   -76,   295,   381,   382,   182,   183,
     184,   185,   186,   121,   187,   188,   184,   185,   186,   383,
     187,   188,   116,   122,   122,   -76,   123,   123,   -76,   127,
     -76,   -76,   128,   187,   188,   129,   388,     2,   443,   444,
       4,   127,     5,     6,   128,     8,     9,   196,   131,   399,
      47,    48,    49,   146,    51,    52,   -27,     1,     2,   132,
       3,     4,   -99,     5,     6,     7,     8,     9,    10,    11,
    -129,  -129,   415,   417,  -129,   254,   255,   256,    43,    43,
     420,   421,   422,   423,   424,   425,   426,   137,    53,   251,
     252,    54,    55,    56,    57,    58,    59,    60,    61,   348,
      62,    63,   349,   133,    13,    64,   127,   435,  -127,   128,
     134,   137,   196,   363,   364,   441,    65,    66,    67,   324,
     135,   497,    68,    69,   356,   366,   432,   121,   349,    70,
     164,   367,   368,   147,   349,   349,    72,   136,     1,     2,
     148,     3,     4,   -99,     5,     6,     7,     8,     9,    10,
      11,   463,   464,    47,    48,    49,    96,    51,    52,     1,
       2,   141,     3,     4,   -99,     5,     6,     7,     8,     9,
      10,    11,   122,   122,   204,   123,   123,   298,   142,   299,
     489,   490,   491,   143,   493,    13,   301,   335,   302,   336,
     304,    53,   305,   191,    54,    55,    56,    57,    58,    59,
      60,    61,   192,    62,    63,    12,    13,   406,    64,   407,
     199,    47,    48,    49,    96,    51,    52,   530,   207,    65,
      66,    67,   450,   211,   451,    68,    69,   476,   537,   477,
     538,   540,    70,   541,    39,   543,    71,   544,   232,    72,
     212,   268,   269,   434,   531,   353,   354,   445,   269,    53,
     222,   547,    54,    55,    56,    57,    58,    59,    60,    61,
     226,    62,    63,   241,   244,   245,    64,   436,   437,   246,
     247,   248,   559,   560,   261,   262,   283,    65,    66,    67,
     263,   567,   264,    68,    69,   233,   265,   266,   267,   284,
      70,   571,   300,   306,    71,   308,   234,    72,    47,    48,
      49,    96,    51,    52,     1,     2,   310,     3,     4,   -99,
       5,     6,     7,     8,     9,    10,    11,   311,   313,   315,
     316,   320,   326,   330,   331,   332,   337,   339,   342,   347,
     386,   357,   350,   358,   359,   361,    53,   387,   360,    54,
      55,    56,    57,    58,    59,    60,    61,   380,    62,    63,
     137,    13,   304,    64,    47,    48,    49,    96,    51,    52,
     305,   390,   389,   296,    65,    66,    67,   391,   392,   396,
      68,    69,   405,   419,   439,   474,   440,    70,   455,   481,
     475,    71,   456,   480,    72,   465,   492,   505,   506,   511,
     524,   488,    53,   532,   510,    54,    55,    56,    57,    58,
      59,    60,    61,   536,    62,    63,   528,   546,   551,    64,
      47,    48,    49,    96,    51,    52,   539,   542,   564,   555,
      65,    66,    67,   545,   552,   553,    68,    69,   554,   556,
     557,   561,   562,    70,   563,   105,   565,    71,    46,   566,
      72,   442,   328,   270,   309,   307,   394,   303,    53,   225,
     370,    54,    55,    56,    57,    58,    59,    60,    61,   478,
      62,    63,   418,     0,   404,    64,    47,    48,    49,    50,
      51,    52,   250,     0,   378,     0,    65,    66,    67,     0,
       0,     0,    68,    69,     0,     0,     0,     0,   416,    70,
       0,     0,     0,    71,     0,     0,    72,     0,     0,     0,
       0,     0,     0,     0,    53,     0,     0,    54,    55,    56,
      57,    58,    59,    60,    61,     0,    62,    63,     0,     0,
       0,    64,    47,    48,    49,    96,    51,    52,     0,     0,
       0,     0,    65,    66,    67,     0,     0,     0,    68,    69,
       0,     0,     0,     0,     0,    70,     0,     0,     0,    71,
       0,     0,    72,     0,     0,     0,     0,     0,     0,     0,
      53,     0,     0,    54,    55,    56,    57,    58,    59,    60,
      61,     0,    62,    63,     0,     0,     0,    64,    47,    48,
      49,   150,    51,   151,     0,     0,     0,     0,    65,    66,
      67,     0,     0,     0,    68,    69,     0,     0,     0,     0,
       0,    70,     0,     0,     0,    71,     0,     0,    72,     0,
       0,     0,     0,     0,     0,     0,    53,     0,     0,    54,
      55,    56,    57,    58,    59,    60,    61,     0,    62,    63,
       0,     0,     0,   152,    47,    48,    49,   150,    51,   151,
       0,     0,     0,     0,    65,    66,    67,     0,     0,     0,
      68,    69,     0,     0,     0,     0,     0,    70,     0,     0,
       0,    71,     0,     0,    72,     0,     0,     0,     0,     0,
       0,     0,    53,     0,     0,    54,    55,    56,    57,    58,
      59,    60,    61,     0,    62,    63,     0,     0,     0,   152,
       0,     0,     0,   166,   167,   168,     0,     0,     0,   170,
      65,    66,    67,   428,     0,     0,    68,    69,     0,     0,
       0,     0,     0,    70,     0,     0,     0,    71,     0,     0,
      72,     0,   171,   172,   173,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   166,
     167,   168,   384,     0,     0,   170,     0,     0,     0,     0,
       0,     0,     0,   176,   177,   178,   198,   180,   181,   182,
     183,   184,   185,   186,     0,   187,   188,     0,   171,   172,
     173,   429,   174,   175,     0,     0,     0,   430,     0,     0,
       0,     0,     0,     0,   166,   167,   168,     0,     0,     0,
     170,     0,     0,     0,     0,     0,     0,     0,     0,   176,
     177,   178,   198,   180,   181,   182,   183,   184,   185,   186,
       0,   187,   188,   171,   172,   173,     0,   174,   175,     0,
       0,     0,     0,   385,     0,     0,     0,     0,     0,     0,
     166,   167,   168,     0,     0,     0,   170,     0,     0,     0,
       0,     0,     0,     0,   176,   177,   178,   198,   180,   181,
     182,   183,   184,   185,   186,     0,   187,   188,     0,   171,
     172,   173,   494,   174,   175,     0,     0,     0,   495,     0,
       0,     0,     0,     0,     0,   166,   167,   168,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,   178,   198,   180,   181,   182,   183,   184,   185,
     186,     0,   187,   188,   171,   172,   173,     0,   174,   175,
       0,     0,     0,     0,   433,     0,     0,     0,     0,     0,
     166,   167,   168,     0,     0,     0,   170,     0,     0,     0,
       0,     0,     0,     0,     0,   176,   177,   178,   198,   180,
     181,   182,   183,   184,   185,   186,     0,   187,   188,   171,
     172,   173,     0,   174,   175,     0,     0,     0,     0,   466,
       0,     0,     0,     0,     0,   166,   167,   168,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,   178,   198,   180,   181,   182,   183,   184,   185,
     186,     0,   187,   188,   171,   172,   173,     0,   174,   175,
       0,     0,     0,     0,   496,     0,     0,     0,     0,     0,
     166,   167,   168,     0,     0,     0,   170,     0,     0,     0,
       0,     0,     0,     0,     0,   176,   177,   178,   198,   180,
     181,   182,   183,   184,   185,   186,     0,   187,   188,   171,
     172,   173,     0,   174,   175,     0,     0,     0,     0,   548,
       0,     0,     0,     0,     0,   166,   167,   168,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,   178,   198,   180,   181,   182,   183,   184,   185,
     186,     0,   187,   188,   171,   172,   173,     0,   174,   175,
       0,     0,     0,     0,   569,     0,     0,     0,     0,     0,
     166,   167,   168,     0,     0,     0,   170,     0,     0,     0,
       0,     0,     0,     0,     0,   176,   177,   178,   198,   180,
     181,   182,   183,   184,   185,   186,     0,   187,   188,   171,
     172,   173,     0,   174,   175,     0,     0,     0,     0,   572,
       0,     0,     0,     0,     0,   166,   167,   168,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,     0,     0,
     176,   177,   178,   198,   180,   181,   182,   183,   184,   185,
     186,     0,   187,   188,   171,   172,   173,     0,   174,   175,
       0,     0,   460,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   166,   167,   168,     0,     0,     0,   170,     0,
       0,     0,     0,     0,     0,   176,   177,   178,   198,   180,
     181,   182,   183,   184,   185,   186,     0,   187,   188,     0,
       0,   171,   172,   173,   260,   174,   175,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   166,
     167,   168,     0,     0,     0,   170,     0,     0,     0,     0,
       0,     0,   176,   177,   178,   198,   180,   181,   182,   183,
     184,   185,   186,     0,   187,   188,     0,     0,   171,   172,
     173,   414,   174,   175,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   166,   167,   168,     0,
       0,     0,   170,     0,     0,     0,     0,     0,     0,   176,
     177,   178,   198,   180,   181,   182,   183,   184,   185,   186,
       0,   187,   188,     0,     0,   171,   172,   173,   525,   174,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   166,   167,   168,     0,     0,     0,   170,
       0,     0,     0,     0,     0,     0,   176,   177,   178,   198,
     180,   181,   182,   183,   184,   185,   186,     0,   187,   188,
       0,     0,   171,   172,   173,   526,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     166,   167,   168,     0,     0,     0,   170,     0,     0,     0,
       0,     0,     0,   176,   177,   178,   198,   180,   181,   182,
     183,   184,   185,   186,     0,   187,   188,     0,     0,   171,
     172,   173,   527,   174,   175,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   166,   167,   168,
       0,     0,     0,   170,     0,     0,     0,     0,     0,     0,
     176,   177,   178,   198,   180,   181,   182,   183,   184,   185,
     186,     0,   187,   188,     0,     0,   171,   172,   173,   529,
     174,   175,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   166,   167,   168,     0,     0,     0,
     170,     0,     0,     0,     0,     0,     0,   176,   177,   178,
     198,   180,   181,   182,   183,   184,   185,   186,     0,   187,
     188,     0,     0,   171,   172,   173,   570,   174,   175,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     166,   167,   168,     0,     0,     0,   170,     0,     0,     0,
       0,     0,     0,     0,   176,   177,   178,   198,   180,   181,
     182,   183,   184,   185,   186,     0,   187,   188,     0,   171,
     172,   173,   438,   174,   175,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   166,   167,   168,     0,
       0,     0,   170,     0,     0,     0,     0,     0,     0,     0,
     176,   177,   178,   198,   180,   181,   182,   183,   184,   185,
     186,     0,   187,   188,     0,   171,   172,   173,   558,   174,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
     168,     0,     0,     0,   170,     0,   176,   177,   178,   198,
     180,   181,   182,   183,   184,   185,   186,     0,   187,   188,
       0,     0,     0,     0,   568,   397,   398,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   166,   167,   168,     0,     0,   169,   170,
       0,     0,     0,     0,     0,     0,     0,     0,   176,   177,
     178,   198,   180,   181,   182,   183,   184,   185,   186,     0,
     187,   188,   171,   172,   173,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
     168,     0,     0,     0,   170,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   197,   187,   188,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   166,   167,   168,     0,     0,     0,   170,
       0,     0,     0,     0,     0,     0,     0,     0,   176,   177,
     178,   198,   180,   181,   182,   183,   184,   185,   186,   216,
     187,   188,   171,   172,   173,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
     168,     0,     0,     0,   170,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,   178,   198,   180,   181,   182,
     183,   184,   185,   186,     0,   187,   188,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   137,   166,   167,   168,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,   176,   177,
     178,   198,   180,   181,   182,   183,   184,   185,   186,     0,
     187,   188,     0,     0,   171,   172,   173,     0,   174,   175,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   362,  -162,  -162,  -162,     0,     0,  -162,  -162,
       0,     0,     0,     0,     0,   176,   177,   178,   198,   180,
     181,   182,   183,   184,   185,   186,     0,   187,   188,     0,
       0,     0,  -162,  -162,  -162,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
     168,     0,     0,     0,   170,     0,     0,     0,     0,     0,
       0,     0,     0,  -162,  -162,  -162,  -162,  -162,  -162,   182,
     183,   184,   185,   186,     0,   187,   188,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   166,   167,   168,     0,   427,     0,   170,
       0,     0,     0,   457,     0,     0,     0,     0,   176,   177,
     178,   198,   180,   181,   182,   183,   184,   185,   186,     0,
     187,   188,   171,   172,   173,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
     168,     0,     0,     0,   170,     0,     0,     0,   458,     0,
       0,     0,     0,   176,   177,   178,   198,   180,   181,   182,
     183,   184,   185,   186,     0,   187,   188,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   166,   167,   168,     0,     0,     0,   170,
       0,     0,     0,   459,     0,     0,     0,     0,   176,   177,
     178,   198,   180,   181,   182,   183,   184,   185,   186,     0,
     187,   188,   171,   172,   173,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
     168,     0,     0,     0,   170,     0,     0,     0,   461,     0,
       0,     0,     0,   176,   177,   178,   198,   180,   181,   182,
     183,   184,   185,   186,     0,   187,   188,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   166,   167,   168,     0,     0,     0,   170,
       0,     0,     0,     0,     0,     0,     0,     0,   176,   177,
     178,   198,   180,   181,   182,   183,   184,   185,   186,     0,
     187,   188,   171,   172,   173,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   166,   167,
     168,     0,   462,     0,   170,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,   178,   198,   180,   181,   182,
     183,   184,   185,   186,     0,   187,   188,   171,   172,   173,
       0,   174,   175,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   166,   167,   168,     0,     0,     0,   170,
       0,     0,     0,     0,     0,     0,     0,     0,   176,   177,
     178,   198,   180,   181,   182,   183,   184,   185,   186,     0,
     187,   188,   171,     0,   173,     0,   174,   175,     0,     0,
       0,     0,     0,     0,     0,   166,   167,   168,     0,     0,
       0,   170,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   176,   177,   178,   198,   180,   181,   182,
     183,   184,   185,   186,   171,   187,   188,     0,   174,   175,
       0,     0,     0,     0,     0,     0,   166,   167,   168,     0,
       0,     0,   170,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   176,   177,   178,   198,   180,
     181,   182,   183,   184,   185,   186,     0,   187,   188,   174,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   176,   177,   178,   198,
     180,   181,   182,   183,   184,   185,   186,     0,   187,   188
};

static const yytype_int16 yycheck[] =
{
       7,    75,   114,   115,   116,   147,   230,   139,   103,   125,
       6,    12,   370,     6,     6,     6,     6,     8,     8,     2,
       6,    52,     8,     6,     6,    20,   344,    45,    35,    86,
       6,    31,    52,    42,    59,    19,    42,    43,    77,    46,
     438,     5,     6,    89,     8,    30,    53,    73,    87,    18,
      76,    65,    21,   411,    23,    24,    63,    26,    27,    90,
      30,    68,    69,    70,    71,    85,    91,    31,    32,     0,
     468,    66,    36,    37,    16,    81,    82,    86,    60,    61,
      89,    77,    31,    92,    60,    61,   228,   438,    81,   447,
     108,    91,    77,   111,   210,   413,    77,   321,    99,   215,
     408,    92,    92,    87,    86,   329,    92,    77,   126,   204,
      86,    92,    52,    46,   106,   231,   438,   468,   250,    88,
     127,   345,   438,   106,    22,   483,    90,   485,   438,   487,
     137,   114,   115,   116,   141,   142,   143,    70,   121,   131,
     147,   124,   450,   451,   452,    85,   468,    77,   131,   507,
     508,   509,   468,   438,     6,    66,     8,    87,   468,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   476,   477,
     478,   178,   179,   180,   181,   182,   183,   184,   185,   186,
      91,   188,   165,   468,    81,     5,     6,    77,     8,    60,
      61,   198,    77,    73,    72,    92,    76,   271,    73,   341,
       3,    76,    92,    81,   211,   212,    58,   214,    88,    12,
       0,    31,    32,    88,    77,    86,    36,    37,    41,   331,
     332,    44,    72,    76,    87,   232,    16,    17,    18,    82,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
       5,     6,    76,     8,   251,    42,    43,     6,    82,     8,
     257,    42,    43,    86,   261,   262,   263,   264,   265,   266,
     267,    91,    52,    93,    88,    89,    31,    32,    92,    59,
      90,    36,    37,     6,    64,     8,   283,   284,    75,    76,
      77,    78,    79,    91,    81,    82,    77,    78,    79,   296,
      81,    82,    86,    73,    73,    85,    76,    76,    88,    86,
      90,    91,    89,    81,    82,    92,   313,    18,    88,    88,
      21,    86,    23,    24,    89,    26,    27,    92,    86,   326,
       3,     4,     5,     6,     7,     8,    16,    17,    18,    86,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      88,    89,   349,   350,    92,   141,   142,   143,   331,   332,
     357,   358,   359,   360,   361,   362,   363,    55,    41,    57,
      58,    44,    45,    46,    47,    48,    49,    50,    51,    88,
      53,    54,    91,    86,    64,    58,    86,   384,    88,    89,
      86,    55,    92,    57,    58,   392,    69,    70,    71,   396,
      86,   465,    75,    76,    88,    88,   379,    91,    91,    82,
      91,    88,    88,    86,    91,    91,    89,    86,    17,    18,
      93,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,   428,   429,     3,     4,     5,     6,     7,     8,    17,
      18,    86,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    73,    73,    53,    76,    76,     6,    86,     8,
     457,   458,   459,    86,   461,    64,     6,     6,     8,     8,
      16,    41,    18,    81,    44,    45,    46,    47,    48,    49,
      50,    51,    91,    53,    54,    63,    64,     6,    58,     8,
       6,     3,     4,     5,     6,     7,     8,   494,     6,    69,
      70,    71,     6,    32,     8,    75,    76,     6,     6,     8,
       8,     6,    82,     8,    86,     6,    86,     8,    30,    89,
      33,    90,    91,    93,   497,    90,    91,    90,    91,    41,
      92,   528,    44,    45,    46,    47,    48,    49,    50,    51,
      76,    53,    54,     6,     6,     6,    58,   386,   387,     6,
       6,     6,   549,   550,    92,    92,    20,    69,    70,    71,
      92,   558,    92,    75,    76,    77,    92,    92,    92,    20,
      82,   568,     6,    59,    86,    59,    88,    89,     3,     4,
       5,     6,     7,     8,    17,    18,     6,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     6,    42,    67,
       5,    91,    34,     6,    86,    86,    89,    92,    74,    88,
      21,    42,    92,    42,    42,    42,    41,    21,    72,    44,
      45,    46,    47,    48,    49,    50,    51,    44,    53,    54,
      55,    64,    16,    58,     3,     4,     5,     6,     7,     8,
      18,    35,    66,    12,    69,    70,    71,     6,    19,    91,
      75,    76,    88,     6,     5,    35,     6,    82,     6,     3,
      68,    86,    88,    12,    89,    88,     6,     6,     5,     3,
      76,    93,    41,    68,    93,    44,    45,    46,    47,    48,
      49,    50,    51,    76,    53,    54,    42,    74,     5,    58,
       3,     4,     5,     6,     7,     8,    93,    93,    74,    76,
      69,    70,    71,    93,    93,    93,    75,    76,    93,    76,
      76,    76,    76,    82,    76,    17,    74,    86,     3,    74,
      89,   396,   214,   164,   195,   194,   320,   192,    41,   121,
     258,    44,    45,    46,    47,    48,    49,    50,    51,   446,
      53,    54,   354,    -1,   337,    58,     3,     4,     5,     6,
       7,     8,   138,    -1,   269,    -1,    69,    70,    71,    -1,
      -1,    -1,    75,    76,    -1,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    86,    -1,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    44,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    54,    -1,    -1,
      -1,    58,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    69,    70,    71,    -1,    -1,    -1,    75,    76,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,
      -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    -1,    -1,    44,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    54,    -1,    -1,    -1,    58,     3,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    69,    70,
      71,    -1,    -1,    -1,    75,    76,    -1,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    -1,    86,    -1,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,    53,    54,
      -1,    -1,    -1,    58,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    -1,    69,    70,    71,    -1,    -1,    -1,
      75,    76,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      -1,    86,    -1,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    44,    45,    46,    47,    48,
      49,    50,    51,    -1,    53,    54,    -1,    -1,    -1,    58,
      -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,    15,
      69,    70,    71,    19,    -1,    -1,    75,    76,    -1,    -1,
      -1,    -1,    -1,    82,    -1,    -1,    -1,    86,    -1,    -1,
      89,    -1,    38,    39,    40,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    -1,    38,    39,
      40,    87,    42,    43,    -1,    -1,    -1,    93,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      -1,    81,    82,    38,    39,    40,    -1,    42,    43,    -1,
      -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    -1,    81,    82,    -1,    38,
      39,    40,    87,    42,    43,    -1,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    38,    39,    40,    -1,    42,    43,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    38,
      39,    40,    -1,    42,    43,    -1,    -1,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    38,    39,    40,    -1,    42,    43,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    38,
      39,    40,    -1,    42,    43,    -1,    -1,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    38,    39,    40,    -1,    42,    43,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    38,
      39,    40,    -1,    42,    43,    -1,    -1,    -1,    -1,    93,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    38,    39,    40,    -1,    42,    43,
      -1,    -1,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     9,    10,    11,    -1,    -1,    -1,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    -1,
      -1,    38,    39,    40,    88,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    81,    82,    -1,    -1,    38,    39,
      40,    88,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    -1,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      -1,    81,    82,    -1,    -1,    38,    39,    40,    88,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    -1,    81,    82,
      -1,    -1,    38,    39,    40,    88,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    -1,    -1,    38,
      39,    40,    88,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    -1,    -1,    38,    39,    40,    88,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    -1,    81,
      82,    -1,    -1,    38,    39,    40,    88,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    -1,    81,    82,    -1,    38,
      39,    40,    87,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    -1,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    -1,    38,    39,    40,    87,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    -1,    -1,    -1,    15,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    -1,    81,    82,
      -1,    -1,    -1,    -1,    87,    36,    37,    38,    39,    40,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    -1,    -1,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    38,    39,    40,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    35,    81,    82,    38,    39,    40,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    35,
      81,    82,    38,    39,    40,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    38,    39,    40,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,     9,    10,    11,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    -1,    -1,    38,    39,    40,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,     9,    10,    11,    -1,    -1,    14,    15,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    -1,
      -1,    -1,    38,    39,    40,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    38,    39,    40,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    -1,    58,    -1,    15,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    38,    39,    40,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    38,    39,    40,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,    15,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    38,    39,    40,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    -1,    -1,    -1,    15,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    38,    39,    40,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    38,    39,    40,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    -1,    58,    -1,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    81,    82,    38,    39,    40,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    -1,    -1,    -1,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    82,    38,    -1,    40,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    -1,    -1,
      -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    38,    81,    82,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    -1,
      -1,    -1,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    -1,    81,    82
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    17,    18,    20,    21,    23,    24,    25,    26,    27,
      28,    29,    63,    64,    95,    96,    97,    98,    99,   100,
     102,   103,   104,   105,   106,   107,   108,   121,   122,   125,
     126,   129,   132,    30,    77,   110,     6,    60,    61,    86,
     133,   134,   135,   136,    30,    77,   110,     3,     4,     5,
       6,     7,     8,    41,    44,    45,    46,    47,    48,    49,
      50,    51,    53,    54,    58,    69,    70,    71,    75,    76,
      82,    86,    89,   119,   120,   136,   143,   144,   145,   146,
     147,   148,   150,   151,   152,   153,   154,   157,   160,   161,
     162,     6,     8,   130,   131,   133,     6,   143,    86,    89,
      96,    65,     0,    52,    85,    99,    16,    22,    77,    31,
     111,   117,   118,   143,    72,    86,    86,     6,     8,    58,
     138,    91,    73,    76,   137,   111,   117,    86,    89,    92,
     143,    86,    86,    86,    86,    86,    86,    55,   143,   158,
     159,    86,    86,    86,   143,   143,     6,    86,    93,   117,
       6,     8,    58,   143,     5,     6,     8,    31,    32,    36,
      37,    90,   164,   165,    91,   137,     9,    10,    11,    14,
      15,    38,    39,    40,    42,    43,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    81,    82,    81,
      92,    81,    91,    59,   123,   124,    92,    35,    72,     6,
      96,    85,    20,    66,    53,    97,   133,     6,   127,   128,
     111,    32,    33,   112,    91,   111,    35,    60,    61,   134,
     134,   134,    92,   140,   141,   135,    76,    76,    82,   136,
     112,   111,    30,    77,    88,   143,   149,     6,    81,   155,
     156,     6,     6,   133,     6,     6,     6,     6,     6,   143,
     158,    57,    58,   159,   149,   149,   149,    42,   138,    93,
      88,    92,    92,    92,    92,    92,    92,    92,    90,    91,
     120,   136,   143,   143,   143,   143,   143,   143,   143,   143,
     143,    41,    44,    20,    20,   143,   143,   143,   143,   143,
     143,   143,   143,   143,     6,     8,    12,   143,     6,     8,
       6,     6,     8,   131,    16,    18,    59,   124,    59,   123,
       6,     6,   143,    42,    90,    67,     5,    97,    66,   101,
      91,   112,   115,   116,   143,   143,    34,   113,   118,   112,
       6,    86,    86,    88,    88,     6,     8,    89,   163,    92,
      76,    82,    74,   138,   113,   112,   143,    88,    88,    91,
      92,     6,    77,    90,    91,    81,    88,    42,    42,    42,
      72,    42,    56,    57,    58,   143,    88,    88,    88,   143,
     140,   143,   143,   143,   143,   143,   143,   143,   165,   137,
      44,   143,   143,   143,    12,    93,    21,    21,   143,    66,
      35,     6,    19,   114,   128,   113,    91,    36,    37,   143,
     113,   134,   134,    90,   164,    88,     6,     8,   138,    77,
      92,   139,   114,   113,    88,   143,    81,   143,   156,     6,
     143,   143,   143,   143,   143,   143,   143,    58,    19,    87,
      93,   163,   136,    93,    93,   143,   119,   119,    87,     5,
       6,   143,   116,    88,    88,    90,    92,   139,     3,    12,
       6,     8,   142,   163,   114,     6,    88,    19,    19,    19,
      91,    19,    58,   143,   143,    88,    93,   106,   109,   121,
     122,   125,   126,   129,    35,    68,     6,     8,   142,   163,
      12,     3,    87,   139,    87,   139,    87,   139,    93,   143,
     143,   143,     6,   143,    87,    93,    93,   137,    88,   106,
     121,   122,   125,   126,   129,     6,     5,   139,   139,   139,
      93,     3,     6,     8,    92,   163,     6,     8,    92,   163,
       6,     8,    92,   163,    76,    88,    88,    88,    42,    88,
     143,   136,    68,   163,   163,   163,    76,     6,     8,    93,
       6,     8,    93,     6,     8,    93,    74,   143,    93,    19,
      87,     5,    93,    93,    93,    76,    76,    76,    87,   143,
     143,    76,    76,    76,    74,    74,    74,   143,    87,    93,
      88,   143,    93
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    95,    95,    96,    96,    96,    97,
      98,    98,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   101,   101,   102,   102,   103,
     103,   103,   104,   104,   105,   106,   107,   108,   108,   108,
     108,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   110,   110,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   116,   116,   117,   117,
     118,   118,   119,   119,   120,   120,   120,   121,   122,   122,
     122,   122,   122,   123,   124,   125,   126,   127,   127,   128,
     129,   130,   130,   131,   131,   131,   131,   131,   132,   132,
     133,   133,   134,   134,   135,   135,   135,   135,   135,   135,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   138,   138,   138,   138,
     139,   139,   139,   139,   139,   139,   140,   140,   141,   141,
     141,   141,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   145,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   147,   147,   147,   147,   148,   149,   149,   150,   150,
     151,   151,   151,   151,   152,   152,   153,   153,   154,   155,
     155,   156,   156,   156,   156,   157,   157,   157,   157,   158,
     158,   159,   160,   160,   160,   160,   160,   160,   161,   161,
     161,   162,   163,   163,   163,   164,   164,   165,   165,   165,
     165,   165,   165,   165
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     3,     1,     3,     4,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     0,     2,     0,     1,     6,
       5,     6,     7,     6,     4,     8,     4,     6,     8,     8,
      10,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     0,     1,     0,     3,     0,     2,     0,
       2,     0,     2,     1,     3,     1,     2,     2,     1,     3,
       1,     3,     1,     3,     3,     3,     3,     2,     2,     3,
       3,     4,     4,     4,     4,     2,     3,     1,     3,     1,
       2,     1,     3,     3,     3,     3,     3,     3,     1,     0,
       1,     3,     1,     3,     1,     3,     6,     4,     6,     4,
       5,     8,    10,    10,    10,     8,    10,    10,    10,     7,
       9,     9,     9,     3,     3,     2,     0,     1,     1,     1,
       0,     1,     2,     4,     3,     3,     0,     1,     2,     2,
       3,     3,     3,     4,     3,     4,     3,     4,     3,     4,
       3,     3,     4,     4,     1,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     4,     3,     2,     3,     4,     3,
       3,     5,     3,     3,     4,     6,     5,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     4,     5,     4,     4,     6,     4,     4,
       4,     8,     8,     8,     8,    12,     1,     3,     2,     3,
       5,     7,     7,     9,    11,    13,     2,     3,     4,     1,
       3,     2,     2,     4,     3,     3,     5,     4,     6,     1,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const yytype_int8 yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const yytype_int8 yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const yytype_int8 yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    13,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     7,     9,
       0,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,    21,     0,    19,    23,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0,   126,     0,   248,     0,   126,     0,   248,     0,   127,
       0,   127,     0,   249,     0,   250,     0,   180,     0,   180,
       0,   110,     0,   110,     0
};


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

# define YYRHSLOC(Rhs, K) ((Rhs)[K].yystate.yyloc)



#undef yynerrs
#define yynerrs (yystackp->yyerrcnt)
#undef yychar
#define yychar (yystackp->yyrawchar)
#undef yylval
#define yylval (yystackp->yyval)
#undef yylloc
#define yylloc (yystackp->yyloc)
#define cypher_yynerrs yynerrs
#define cypher_yychar yychar
#define cypher_yylval yylval
#define cypher_yylloc yylloc

enum { YYENOMEM = -2 };

typedef enum { yyok, yyaccept, yyabort, yyerr, yynomem } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif

/** State numbers. */
typedef int yy_state_t;

/** Rule numbers. */
typedef int yyRuleNum;

/** Item references. */
typedef short yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState
{
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yyval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_t yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  YYPTRDIFF_T yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  nonterminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yyval;
  } yysemantics;
  /** Source location for this state.  */
  YYLTYPE yyloc;
};

struct yyGLRStateSet
{
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != CYPHER_CYPHER_YYEMPTY.  */
  yybool* yylookaheadNeeds;
  YYPTRDIFF_T yysize;
  YYPTRDIFF_T yycapacity;
};

struct yySemanticOption
{
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;
  /* To compute the location of the error token.  */
  yyGLRStackItem yyerror_range[3];

  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;
  YYLTYPE yyloc;

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  YYPTRDIFF_T yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

_Noreturn static void
yyFail (yyGLRStack* yystackp, YYLTYPE *yylocp, cypher_parser_context *context, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (yylocp, context, yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

_Noreturn static void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

/** Accessing symbol of state YYSTATE.  */
static inline yysymbol_kind_t
yy_accessing_symbol (yy_state_t yystate)
{
  return YY_CAST (yysymbol_kind_t, yystos[yystate]);
}

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "INTEGER", "DECIMAL", "STRING",
  "IDENTIFIER", "PARAMETER", "BQIDENT", "NOT_EQ", "LT_EQ", "GT_EQ",
  "DOT_DOT", "TYPECAST", "PLUS_EQ", "REGEX_MATCH", "MATCH", "RETURN",
  "CREATE", "WHERE", "WITH", "SET", "DELETE", "REMOVE", "MERGE", "UNWIND",
  "DETACH", "FOREACH", "CALL", "OPTIONAL", "DISTINCT", "ORDER", "BY",
  "SKIP", "LIMIT", "AS", "ASC", "DESC", "AND", "OR", "XOR", "NOT", "IN",
  "IS", "NULL_P", "TRUE_P", "FALSE_P", "EXISTS", "ANY", "NONE", "SINGLE",
  "REDUCE", "UNION", "ALL", "CASE", "WHEN", "THEN", "ELSE", "END_P", "ON",
  "SHORTESTPATH", "ALLSHORTESTPATHS", "PATTERN", "EXPLAIN", "LOAD", "CSV",
  "FROM", "HEADERS", "FIELDTERMINATOR", "STARTS", "ENDS", "CONTAINS",
  "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "'.'",
  "'['", "UNARY_MINUS", "UNARY_PLUS", "';'", "'('", "'|'", "')'", "'{'",
  "'}'", "','", "':'", "']'", "$accept", "stmt", "union_query",
  "single_query", "clause_list", "clause", "match_clause",
  "from_graph_opt", "optional_opt", "return_clause", "with_clause",
  "unwind_clause", "foreach_clause", "call_clause", "load_csv_clause",
  "foreach_update_list", "distinct_opt", "order_by_opt", "skip_opt",
  "limit_opt", "where_opt", "order_by_list", "order_by_item",
  "return_item_list", "return_item", "set_item_list", "set_item",
  "create_clause", "merge_clause", "on_create_clause", "on_match_clause",
  "set_clause", "delete_clause", "delete_item_list", "delete_item",
  "remove_clause", "remove_item_list", "remove_item", "detach_opt",
  "pattern_list", "simple_path", "path", "node_pattern", "rel_pattern",
  "variable_opt", "varlen_range_opt", "label_opt", "label_list",
  "rel_type_list", "expr", "primary_expr", "literal_expr", "function_call",
  "list_predicate", "reduce_expr", "argument_list", "list_literal",
  "list_comprehension", "pattern_comprehension", "map_literal",
  "map_projection", "map_projection_list", "map_projection_item",
  "case_expression", "when_clause_list", "when_clause", "literal",
  "identifier", "parameter", "properties_opt", "map_pair_list", "map_pair", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yysymbol_kind_t
yylhsNonterm (yyRuleNum yyrule)
{
  return YY_CAST (yysymbol_kind_t, yyr1[yyrule]);
}

#if CYPHER_YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

# define YY_FPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_FPRINTF_

# define YY_FPRINTF_(Args)                      \
  do {                                          \
    YYFPRINTF Args;                             \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)

# define YY_DPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_DPRINTF_

# define YY_DPRINTF_(Args)                      \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined CYPHER_YYLTYPE_IS_TRIVIAL && CYPHER_YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */



/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, cypher_parser_context *context)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (context);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, cypher_parser_context *context)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, context);
  YYFPRINTF (yyo, ")");
}

# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YY_FPRINTF ((stderr, "%s ", Title));                            \
        yy_symbol_print (stderr, Kind, Value, Location, context);        \
        YY_FPRINTF ((stderr, "\n"));                                    \
      }                                                                 \
  } while (0)

static inline void
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, YYPTRDIFF_T yyk,
                 yyRuleNum yyrule, cypher_parser_context *context);

# define YY_REDUCE_PRINT(Args)          \
  do {                                  \
    if (yydebug)                        \
      yy_reduce_print Args;             \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

static void yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !CYPHER_YYDEBUG */

# define YY_DPRINTF(Args) do {} while (yyfalse)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_REDUCE_PRINT(Args)

#endif /* !CYPHER_YYDEBUG */

#ifndef yystrlen
# define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if CYPHER_YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yyval = s->yysemantics.yyval;
      else
        /* The effect of using yyval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      yyvsp[i].yystate.yyloc = s->yyloc;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}


/** If yychar is empty, fetch the next token.  */
static inline yysymbol_kind_t
yygetToken (int *yycharp, yyGLRStack* yystackp, cypher_parser_context *context)
{
  yysymbol_kind_t yytoken;
  YY_USE (context);
  if (*yycharp == CYPHER_CYPHER_YYEMPTY)
    {
      YY_DPRINTF ((stderr, "Reading a token\n"));
      *yycharp = yylex (&yylval, &yylloc, context);
    }
  if (*yycharp <= CYPHER_YYEOF)
    {
      *yycharp = CYPHER_YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YY_DPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (*yycharp);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }
  return yytoken;
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT, yynomem for YYNOMEM.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyrule, int yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp, YYPTRDIFF_T yyk,
              YYSTYPE* yyvalp, YYLTYPE *yylocp, cypher_parser_context *context)
{
  const yybool yynormal YY_ATTRIBUTE_UNUSED = yystackp->yysplitPoint == YY_NULLPTR;
  int yylow = 1;
  YY_USE (yyvalp);
  YY_USE (yylocp);
  YY_USE (context);
  YY_USE (yyk);
  YY_USE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYNOMEM
# define YYNOMEM return yynomem
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = CYPHER_CYPHER_YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, (N), yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (yylocp, context, YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yyval;
  /* Default location. */
  YYLLOC_DEFAULT ((*yylocp), (yyvsp - yyrhslen), yyrhslen);
  yystackp->yyerror_range[1].yystate.yyloc = *yylocp;
  /* If yyk == -1, we are running a deferred action on a temporary
     stack.  In that case, YY_REDUCE_PRINT must not play with YYFILL,
     so pretend the stack is "normal". */
  YY_REDUCE_PRINT ((yynormal || yyk == -1, yyvsp, yyk, yyrule, context));
  switch (yyrule)
    {
  case 2: /* stmt: union_query  */
#line 167 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
            context->result = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
        }
#line 2437 "build/parser/cypher_gram.tab.c"
    break;

  case 3: /* stmt: union_query ';'  */
#line 172 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node);
            context->result = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node);
        }
#line 2446 "build/parser/cypher_gram.tab.c"
    break;

  case 4: /* stmt: EXPLAIN union_query  */
#line 177 "src/backend/parser/cypher_gram.y"
        {
            /* For EXPLAIN with UNION, wrap if needed */
            if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node)->type == AST_NODE_QUERY) {
                ((cypher_query*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node))->explain = true;
            }
            ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
            context->result = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
        }
#line 2459 "build/parser/cypher_gram.tab.c"
    break;

  case 5: /* stmt: EXPLAIN union_query ';'  */
#line 186 "src/backend/parser/cypher_gram.y"
        {
            if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node)->type == AST_NODE_QUERY) {
                ((cypher_query*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node))->explain = true;
            }
            ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node);
            context->result = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node);
        }
#line 2471 "build/parser/cypher_gram.tab.c"
    break;

  case 6: /* union_query: single_query  */
#line 197 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
        }
#line 2479 "build/parser/cypher_gram.tab.c"
    break;

  case 7: /* union_query: union_query UNION single_query  */
#line 201 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_cypher_union((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line);
        }
#line 2487 "build/parser/cypher_gram.tab.c"
    break;

  case 8: /* union_query: union_query UNION ALL single_query  */
#line 205 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_cypher_union((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), true, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 2495 "build/parser/cypher_gram.tab.c"
    break;

  case 9: /* single_query: clause_list  */
#line 212 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_cypher_query((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list), false);
        }
#line 2503 "build/parser/cypher_gram.tab.c"
    break;

  case 10: /* clause_list: clause  */
#line 219 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 2512 "build/parser/cypher_gram.tab.c"
    break;

  case 11: /* clause_list: clause_list clause  */
#line 224 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list);
        }
#line 2521 "build/parser/cypher_gram.tab.c"
    break;

  case 12: /* clause: match_clause  */
#line 231 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.match); }
#line 2527 "build/parser/cypher_gram.tab.c"
    break;

  case 13: /* clause: return_clause  */
#line 232 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.return_clause); }
#line 2533 "build/parser/cypher_gram.tab.c"
    break;

  case 14: /* clause: with_clause  */
#line 233 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.with_clause); }
#line 2539 "build/parser/cypher_gram.tab.c"
    break;

  case 15: /* clause: unwind_clause  */
#line 234 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 2545 "build/parser/cypher_gram.tab.c"
    break;

  case 16: /* clause: foreach_clause  */
#line 235 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 2551 "build/parser/cypher_gram.tab.c"
    break;

  case 17: /* clause: load_csv_clause  */
#line 236 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 2557 "build/parser/cypher_gram.tab.c"
    break;

  case 18: /* clause: create_clause  */
#line 237 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.create); }
#line 2563 "build/parser/cypher_gram.tab.c"
    break;

  case 19: /* clause: merge_clause  */
#line 238 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.merge); }
#line 2569 "build/parser/cypher_gram.tab.c"
    break;

  case 20: /* clause: set_clause  */
#line 239 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.set); }
#line 2575 "build/parser/cypher_gram.tab.c"
    break;

  case 21: /* clause: delete_clause  */
#line 240 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.delete); }
#line 2581 "build/parser/cypher_gram.tab.c"
    break;

  case 22: /* clause: remove_clause  */
#line 241 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.remove); }
#line 2587 "build/parser/cypher_gram.tab.c"
    break;

  case 23: /* clause: call_clause  */
#line 242 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 2593 "build/parser/cypher_gram.tab.c"
    break;

  case 24: /* match_clause: optional_opt MATCH pattern_list from_graph_opt where_opt  */
#line 248 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).match) = make_cypher_match((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.boolean), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string));
        }
#line 2601 "build/parser/cypher_gram.tab.c"
    break;

  case 25: /* from_graph_opt: %empty  */
#line 254 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).string) = NULL; }
#line 2607 "build/parser/cypher_gram.tab.c"
    break;

  case 26: /* from_graph_opt: FROM IDENTIFIER  */
#line 256 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).string) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string);
        }
#line 2615 "build/parser/cypher_gram.tab.c"
    break;

  case 27: /* optional_opt: %empty  */
#line 262 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).boolean) = false; }
#line 2621 "build/parser/cypher_gram.tab.c"
    break;

  case 28: /* optional_opt: OPTIONAL  */
#line 263 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).boolean) = true; }
#line 2627 "build/parser/cypher_gram.tab.c"
    break;

  case 29: /* return_clause: RETURN distinct_opt return_item_list order_by_opt skip_opt limit_opt  */
#line 269 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).return_clause) = make_cypher_return((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.boolean), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 2635 "build/parser/cypher_gram.tab.c"
    break;

  case 30: /* return_clause: RETURN '*' order_by_opt skip_opt limit_opt  */
#line 273 "src/backend/parser/cypher_gram.y"
        {
            /* RETURN * - return all bound variables (items=NULL signals star) */
            ((*yyvalp).return_clause) = make_cypher_return(false, NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 2644 "build/parser/cypher_gram.tab.c"
    break;

  case 31: /* return_clause: RETURN DISTINCT '*' order_by_opt skip_opt limit_opt  */
#line 278 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).return_clause) = make_cypher_return(true, NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 2652 "build/parser/cypher_gram.tab.c"
    break;

  case 32: /* with_clause: WITH distinct_opt return_item_list order_by_opt skip_opt limit_opt where_opt  */
#line 286 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).with_clause) = make_cypher_with((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.boolean), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 2660 "build/parser/cypher_gram.tab.c"
    break;

  case 33: /* with_clause: WITH '*' order_by_opt skip_opt limit_opt where_opt  */
#line 290 "src/backend/parser/cypher_gram.y"
        {
            /* WITH * - pass all variables through */
            ((*yyvalp).with_clause) = make_cypher_with(false, NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 2669 "build/parser/cypher_gram.tab.c"
    break;

  case 34: /* unwind_clause: UNWIND expr AS IDENTIFIER  */
#line 299 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_cypher_unwind((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 2678 "build/parser/cypher_gram.tab.c"
    break;

  case 35: /* foreach_clause: FOREACH '(' IDENTIFIER IN expr '|' foreach_update_list ')'  */
#line 308 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_cypher_foreach((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 2687 "build/parser/cypher_gram.tab.c"
    break;

  case 36: /* call_clause: CALL '{' union_query '}'  */
#line 321 "src/backend/parser/cypher_gram.y"
        {
            ast_list *branches = ast_list_create();
            ast_list_append(branches, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node));
            ((*yyvalp).node) = (ast_node*)make_cypher_call_subquery(branches, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
        }
#line 2697 "build/parser/cypher_gram.tab.c"
    break;

  case 37: /* load_csv_clause: LOAD CSV FROM STRING AS IDENTIFIER  */
#line 331 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_cypher_load_csv((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), false, NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 2707 "build/parser/cypher_gram.tab.c"
    break;

  case 38: /* load_csv_clause: LOAD CSV WITH HEADERS FROM STRING AS IDENTIFIER  */
#line 337 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_cypher_load_csv((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), true, NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 2717 "build/parser/cypher_gram.tab.c"
    break;

  case 39: /* load_csv_clause: LOAD CSV FROM STRING AS IDENTIFIER FIELDTERMINATOR STRING  */
#line 343 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_cypher_load_csv((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 2728 "build/parser/cypher_gram.tab.c"
    break;

  case 40: /* load_csv_clause: LOAD CSV WITH HEADERS FROM STRING AS IDENTIFIER FIELDTERMINATOR STRING  */
#line 350 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_cypher_load_csv((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), true, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 2739 "build/parser/cypher_gram.tab.c"
    break;

  case 41: /* foreach_update_list: create_clause  */
#line 361 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.create));
        }
#line 2748 "build/parser/cypher_gram.tab.c"
    break;

  case 42: /* foreach_update_list: set_clause  */
#line 366 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.set));
        }
#line 2757 "build/parser/cypher_gram.tab.c"
    break;

  case 43: /* foreach_update_list: delete_clause  */
#line 371 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.delete));
        }
#line 2766 "build/parser/cypher_gram.tab.c"
    break;

  case 44: /* foreach_update_list: merge_clause  */
#line 376 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.merge));
        }
#line 2775 "build/parser/cypher_gram.tab.c"
    break;

  case 45: /* foreach_update_list: remove_clause  */
#line 381 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.remove));
        }
#line 2784 "build/parser/cypher_gram.tab.c"
    break;

  case 46: /* foreach_update_list: foreach_clause  */
#line 386 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 2793 "build/parser/cypher_gram.tab.c"
    break;

  case 47: /* foreach_update_list: foreach_update_list create_clause  */
#line 391 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.create));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list);
        }
#line 2802 "build/parser/cypher_gram.tab.c"
    break;

  case 48: /* foreach_update_list: foreach_update_list set_clause  */
#line 396 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.set));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list);
        }
#line 2811 "build/parser/cypher_gram.tab.c"
    break;

  case 49: /* foreach_update_list: foreach_update_list delete_clause  */
#line 401 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.delete));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list);
        }
#line 2820 "build/parser/cypher_gram.tab.c"
    break;

  case 50: /* foreach_update_list: foreach_update_list merge_clause  */
#line 406 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.merge));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list);
        }
#line 2829 "build/parser/cypher_gram.tab.c"
    break;

  case 51: /* foreach_update_list: foreach_update_list remove_clause  */
#line 411 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.remove));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list);
        }
#line 2838 "build/parser/cypher_gram.tab.c"
    break;

  case 52: /* foreach_update_list: foreach_update_list foreach_clause  */
#line 416 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list);
        }
#line 2847 "build/parser/cypher_gram.tab.c"
    break;

  case 53: /* distinct_opt: %empty  */
#line 423 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).boolean) = false; }
#line 2853 "build/parser/cypher_gram.tab.c"
    break;

  case 54: /* distinct_opt: DISTINCT  */
#line 424 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).boolean) = true; }
#line 2859 "build/parser/cypher_gram.tab.c"
    break;

  case 55: /* order_by_opt: %empty  */
#line 428 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).list) = NULL; }
#line 2865 "build/parser/cypher_gram.tab.c"
    break;

  case 56: /* order_by_opt: ORDER BY order_by_list  */
#line 429 "src/backend/parser/cypher_gram.y"
                             { ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list); }
#line 2871 "build/parser/cypher_gram.tab.c"
    break;

  case 57: /* skip_opt: %empty  */
#line 433 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).node) = NULL; }
#line 2877 "build/parser/cypher_gram.tab.c"
    break;

  case 58: /* skip_opt: SKIP expr  */
#line 434 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 2883 "build/parser/cypher_gram.tab.c"
    break;

  case 59: /* limit_opt: %empty  */
#line 438 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).node) = NULL; }
#line 2889 "build/parser/cypher_gram.tab.c"
    break;

  case 60: /* limit_opt: LIMIT expr  */
#line 439 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 2895 "build/parser/cypher_gram.tab.c"
    break;

  case 61: /* where_opt: %empty  */
#line 443 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).node) = NULL; }
#line 2901 "build/parser/cypher_gram.tab.c"
    break;

  case 62: /* where_opt: WHERE expr  */
#line 444 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 2907 "build/parser/cypher_gram.tab.c"
    break;

  case 63: /* order_by_list: order_by_item  */
#line 449 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_item));
        }
#line 2916 "build/parser/cypher_gram.tab.c"
    break;

  case 64: /* order_by_list: order_by_list ',' order_by_item  */
#line 454 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.order_by_item));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
        }
#line 2925 "build/parser/cypher_gram.tab.c"
    break;

  case 65: /* order_by_item: expr  */
#line 461 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).order_by_item) = make_order_by_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), false); /* Default is ASC */ }
#line 2931 "build/parser/cypher_gram.tab.c"
    break;

  case 66: /* order_by_item: expr ASC  */
#line 462 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).order_by_item) = make_order_by_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), false); }
#line 2937 "build/parser/cypher_gram.tab.c"
    break;

  case 67: /* order_by_item: expr DESC  */
#line 463 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).order_by_item) = make_order_by_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), true); }
#line 2943 "build/parser/cypher_gram.tab.c"
    break;

  case 68: /* return_item_list: return_item  */
#line 469 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.return_item));
        }
#line 2952 "build/parser/cypher_gram.tab.c"
    break;

  case 69: /* return_item_list: return_item_list ',' return_item  */
#line 474 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.return_item));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
        }
#line 2961 "build/parser/cypher_gram.tab.c"
    break;

  case 70: /* return_item: expr  */
#line 482 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).return_item) = make_return_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), NULL);
        }
#line 2969 "build/parser/cypher_gram.tab.c"
    break;

  case 71: /* return_item: expr AS IDENTIFIER  */
#line 486 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).return_item) = make_return_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 2978 "build/parser/cypher_gram.tab.c"
    break;

  case 72: /* set_item_list: set_item  */
#line 494 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.set_item));
        }
#line 2987 "build/parser/cypher_gram.tab.c"
    break;

  case 73: /* set_item_list: set_item_list ',' set_item  */
#line 499 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.set_item));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
        }
#line 2996 "build/parser/cypher_gram.tab.c"
    break;

  case 74: /* set_item: expr '=' expr  */
#line 507 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).set_item) = make_cypher_set_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), false);
        }
#line 3004 "build/parser/cypher_gram.tab.c"
    break;

  case 75: /* set_item: expr PLUS_EQ expr  */
#line 511 "src/backend/parser/cypher_gram.y"
        {
            /* SET n += {map} — merge properties */
            ((*yyvalp).set_item) = make_cypher_set_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), true);
        }
#line 3013 "build/parser/cypher_gram.tab.c"
    break;

  case 76: /* set_item: IDENTIFIER ':' IDENTIFIER  */
#line 516 "src/backend/parser/cypher_gram.y"
        {
            /* SET n:Label syntax */
            cypher_identifier *var = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            cypher_label_expr *label = make_label_expr((ast_node*)var, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ((*yyvalp).set_item) = make_cypher_set_item((ast_node*)label, NULL, false);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3026 "build/parser/cypher_gram.tab.c"
    break;

  case 77: /* create_clause: CREATE pattern_list  */
#line 529 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).create) = make_cypher_create((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list));
        }
#line 3034 "build/parser/cypher_gram.tab.c"
    break;

  case 78: /* merge_clause: MERGE pattern_list  */
#line 537 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).merge) = make_cypher_merge((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list), NULL, NULL);
        }
#line 3042 "build/parser/cypher_gram.tab.c"
    break;

  case 79: /* merge_clause: MERGE pattern_list on_create_clause  */
#line 541 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).merge) = make_cypher_merge((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list), NULL);
        }
#line 3050 "build/parser/cypher_gram.tab.c"
    break;

  case 80: /* merge_clause: MERGE pattern_list on_match_clause  */
#line 545 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).merge) = make_cypher_merge((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list));
        }
#line 3058 "build/parser/cypher_gram.tab.c"
    break;

  case 81: /* merge_clause: MERGE pattern_list on_create_clause on_match_clause  */
#line 549 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).merge) = make_cypher_merge((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list));
        }
#line 3066 "build/parser/cypher_gram.tab.c"
    break;

  case 82: /* merge_clause: MERGE pattern_list on_match_clause on_create_clause  */
#line 553 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).merge) = make_cypher_merge((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list));
        }
#line 3074 "build/parser/cypher_gram.tab.c"
    break;

  case 83: /* on_create_clause: ON CREATE SET set_item_list  */
#line 560 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list);
        }
#line 3082 "build/parser/cypher_gram.tab.c"
    break;

  case 84: /* on_match_clause: ON MATCH SET set_item_list  */
#line 567 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list);
        }
#line 3090 "build/parser/cypher_gram.tab.c"
    break;

  case 85: /* set_clause: SET set_item_list  */
#line 575 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).set) = make_cypher_set((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list));
        }
#line 3098 "build/parser/cypher_gram.tab.c"
    break;

  case 86: /* delete_clause: detach_opt DELETE delete_item_list  */
#line 583 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).delete) = make_cypher_delete((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.boolean));
        }
#line 3106 "build/parser/cypher_gram.tab.c"
    break;

  case 87: /* delete_item_list: delete_item  */
#line 590 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.delete_item));
        }
#line 3115 "build/parser/cypher_gram.tab.c"
    break;

  case 88: /* delete_item_list: delete_item_list ',' delete_item  */
#line 595 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.delete_item));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
        }
#line 3124 "build/parser/cypher_gram.tab.c"
    break;

  case 89: /* delete_item: IDENTIFIER  */
#line 603 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).delete_item) = make_delete_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3133 "build/parser/cypher_gram.tab.c"
    break;

  case 90: /* remove_clause: REMOVE remove_item_list  */
#line 612 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).remove) = make_cypher_remove((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list));
        }
#line 3141 "build/parser/cypher_gram.tab.c"
    break;

  case 91: /* remove_item_list: remove_item  */
#line 619 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.remove_item));
        }
#line 3150 "build/parser/cypher_gram.tab.c"
    break;

  case 92: /* remove_item_list: remove_item_list ',' remove_item  */
#line 624 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.remove_item));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
        }
#line 3159 "build/parser/cypher_gram.tab.c"
    break;

  case 93: /* remove_item: IDENTIFIER '.' IDENTIFIER  */
#line 632 "src/backend/parser/cypher_gram.y"
        {
            /* REMOVE n.property - property access */
            cypher_identifier *base = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            ast_node *prop = (ast_node*)make_property((ast_node*)base, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ((*yyvalp).remove_item) = make_remove_item(prop);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3172 "build/parser/cypher_gram.tab.c"
    break;

  case 94: /* remove_item: IDENTIFIER '.' BQIDENT  */
#line 641 "src/backend/parser/cypher_gram.y"
        {
            /* REMOVE n.`special-key` - backtick-quoted property */
            cypher_identifier *base = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            ast_node *prop = (ast_node*)make_property((ast_node*)base, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ((*yyvalp).remove_item) = make_remove_item(prop);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3185 "build/parser/cypher_gram.tab.c"
    break;

  case 95: /* remove_item: BQIDENT '.' IDENTIFIER  */
#line 650 "src/backend/parser/cypher_gram.y"
        {
            /* REMOVE `special-var`.property */
            cypher_identifier *base = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            ast_node *prop = (ast_node*)make_property((ast_node*)base, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ((*yyvalp).remove_item) = make_remove_item(prop);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3198 "build/parser/cypher_gram.tab.c"
    break;

  case 96: /* remove_item: BQIDENT '.' BQIDENT  */
#line 659 "src/backend/parser/cypher_gram.y"
        {
            /* REMOVE `special-var`.`special-key` */
            cypher_identifier *base = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            ast_node *prop = (ast_node*)make_property((ast_node*)base, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ((*yyvalp).remove_item) = make_remove_item(prop);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3211 "build/parser/cypher_gram.tab.c"
    break;

  case 97: /* remove_item: IDENTIFIER ':' IDENTIFIER  */
#line 668 "src/backend/parser/cypher_gram.y"
        {
            /* REMOVE n:Label syntax */
            cypher_identifier *var = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            cypher_label_expr *label = make_label_expr((ast_node*)var, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ((*yyvalp).remove_item) = make_remove_item((ast_node*)label);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3224 "build/parser/cypher_gram.tab.c"
    break;

  case 98: /* detach_opt: DETACH  */
#line 680 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).boolean) = true;
        }
#line 3232 "build/parser/cypher_gram.tab.c"
    break;

  case 99: /* detach_opt: %empty  */
#line 684 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).boolean) = false;
        }
#line 3240 "build/parser/cypher_gram.tab.c"
    break;

  case 100: /* pattern_list: path  */
#line 692 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.path));
        }
#line 3249 "build/parser/cypher_gram.tab.c"
    break;

  case 101: /* pattern_list: pattern_list ',' path  */
#line 697 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.path));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
        }
#line 3258 "build/parser/cypher_gram.tab.c"
    break;

  case 102: /* simple_path: node_pattern  */
#line 706 "src/backend/parser/cypher_gram.y"
        {
            ast_list *elements = ast_list_create();
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node_pattern));
            ((*yyvalp).path) = make_path(elements);
        }
#line 3268 "build/parser/cypher_gram.tab.c"
    break;

  case 103: /* simple_path: simple_path rel_pattern node_pattern  */
#line 712 "src/backend/parser/cypher_gram.y"
        {
            /* Create a new list copying elements from the existing path */
            ast_list *new_elements = ast_list_create();
            for (int i = 0; i < (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.path)->elements->count; i++) {
                ast_list_append(new_elements, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.path)->elements->items[i]);
            }
            ast_list_append(new_elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.rel_pattern));
            ast_list_append(new_elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node_pattern));

            /* Note: Let Bison handle memory cleanup of $1 automatically */
            /* Manual freeing during parsing can cause parser state corruption */

            ((*yyvalp).path) = make_path(new_elements);
        }
#line 3287 "build/parser/cypher_gram.tab.c"
    break;

  case 104: /* path: simple_path  */
#line 731 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).path) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.path);
        }
#line 3295 "build/parser/cypher_gram.tab.c"
    break;

  case 105: /* path: IDENTIFIER '=' simple_path  */
#line 735 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).path) = make_path_with_var((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.path)->elements);
            /* Free the anonymous path structure, but keep its elements */
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.path));
        }
#line 3305 "build/parser/cypher_gram.tab.c"
    break;

  case 106: /* path: IDENTIFIER '=' SHORTESTPATH '(' simple_path ')'  */
#line 741 "src/backend/parser/cypher_gram.y"
        {
            cypher_path *sp = make_shortest_path((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.path)->elements, PATH_TYPE_SHORTEST);
            sp->var_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);
            ((*yyvalp).path) = sp;
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.path));
        }
#line 3316 "build/parser/cypher_gram.tab.c"
    break;

  case 107: /* path: SHORTESTPATH '(' simple_path ')'  */
#line 748 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).path) = make_shortest_path((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.path)->elements, PATH_TYPE_SHORTEST);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.path));
        }
#line 3325 "build/parser/cypher_gram.tab.c"
    break;

  case 108: /* path: IDENTIFIER '=' ALLSHORTESTPATHS '(' simple_path ')'  */
#line 753 "src/backend/parser/cypher_gram.y"
        {
            cypher_path *sp = make_shortest_path((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.path)->elements, PATH_TYPE_ALL_SHORTEST);
            sp->var_name = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string);
            ((*yyvalp).path) = sp;
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.path));
        }
#line 3336 "build/parser/cypher_gram.tab.c"
    break;

  case 109: /* path: ALLSHORTESTPATHS '(' simple_path ')'  */
#line 760 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).path) = make_shortest_path((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.path)->elements, PATH_TYPE_ALL_SHORTEST);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.path));
        }
#line 3345 "build/parser/cypher_gram.tab.c"
    break;

  case 110: /* node_pattern: '(' variable_opt label_opt properties_opt ')'  */
#line 768 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node_pattern) = make_node_pattern((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.map));
        }
#line 3353 "build/parser/cypher_gram.tab.c"
    break;

  case 111: /* rel_pattern: '-' '[' variable_opt varlen_range_opt properties_opt ']' '-' '>'  */
#line 783 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), NULL, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.map), false, true, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.varlen_range));
        }
#line 3361 "build/parser/cypher_gram.tab.c"
    break;

  case 112: /* rel_pattern: '-' '[' variable_opt ':' IDENTIFIER varlen_range_opt properties_opt ']' '-' '>'  */
#line 787 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.map), false, true, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.varlen_range));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 3370 "build/parser/cypher_gram.tab.c"
    break;

  case 113: /* rel_pattern: '-' '[' variable_opt ':' BQIDENT varlen_range_opt properties_opt ']' '-' '>'  */
#line 792 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.map), false, true, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.varlen_range));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 3379 "build/parser/cypher_gram.tab.c"
    break;

  case 114: /* rel_pattern: '-' '[' variable_opt ':' rel_type_list varlen_range_opt properties_opt ']' '-' '>'  */
#line 797 "src/backend/parser/cypher_gram.y"
        {
            cypher_rel_pattern *p = make_rel_pattern_multi_type((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.map), false, true);
            if (p) p->varlen = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.varlen_range);
            ((*yyvalp).rel_pattern) = p;
        }
#line 3389 "build/parser/cypher_gram.tab.c"
    break;

  case 115: /* rel_pattern: '<' '-' '[' variable_opt varlen_range_opt properties_opt ']' '-'  */
#line 804 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string), NULL, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.map), true, false, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.varlen_range));
        }
#line 3397 "build/parser/cypher_gram.tab.c"
    break;

  case 116: /* rel_pattern: '<' '-' '[' variable_opt ':' IDENTIFIER varlen_range_opt properties_opt ']' '-'  */
#line 808 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.map), true, false, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.varlen_range));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));
        }
#line 3406 "build/parser/cypher_gram.tab.c"
    break;

  case 117: /* rel_pattern: '<' '-' '[' variable_opt ':' BQIDENT varlen_range_opt properties_opt ']' '-'  */
#line 813 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.map), true, false, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.varlen_range));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));
        }
#line 3415 "build/parser/cypher_gram.tab.c"
    break;

  case 118: /* rel_pattern: '<' '-' '[' variable_opt ':' rel_type_list varlen_range_opt properties_opt ']' '-'  */
#line 818 "src/backend/parser/cypher_gram.y"
        {
            cypher_rel_pattern *p = make_rel_pattern_multi_type((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.map), true, false);
            if (p) p->varlen = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.varlen_range);
            ((*yyvalp).rel_pattern) = p;
        }
#line 3425 "build/parser/cypher_gram.tab.c"
    break;

  case 119: /* rel_pattern: '-' '[' variable_opt varlen_range_opt properties_opt ']' '-'  */
#line 825 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string), NULL, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.map), false, false, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.varlen_range));
        }
#line 3433 "build/parser/cypher_gram.tab.c"
    break;

  case 120: /* rel_pattern: '-' '[' variable_opt ':' IDENTIFIER varlen_range_opt properties_opt ']' '-'  */
#line 829 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.map), false, false, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.varlen_range));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));
        }
#line 3442 "build/parser/cypher_gram.tab.c"
    break;

  case 121: /* rel_pattern: '-' '[' variable_opt ':' BQIDENT varlen_range_opt properties_opt ']' '-'  */
#line 834 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.map), false, false, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.varlen_range));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));
        }
#line 3451 "build/parser/cypher_gram.tab.c"
    break;

  case 122: /* rel_pattern: '-' '[' variable_opt ':' rel_type_list varlen_range_opt properties_opt ']' '-'  */
#line 839 "src/backend/parser/cypher_gram.y"
        {
            cypher_rel_pattern *p = make_rel_pattern_multi_type((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.map), false, false);
            if (p) p->varlen = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.varlen_range);
            ((*yyvalp).rel_pattern) = p;
        }
#line 3461 "build/parser/cypher_gram.tab.c"
    break;

  case 123: /* rel_pattern: '-' '-' '>'  */
#line 846 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen(NULL, NULL, NULL, false, true, NULL);
        }
#line 3469 "build/parser/cypher_gram.tab.c"
    break;

  case 124: /* rel_pattern: '<' '-' '-'  */
#line 850 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen(NULL, NULL, NULL, true, false, NULL);
        }
#line 3477 "build/parser/cypher_gram.tab.c"
    break;

  case 125: /* rel_pattern: '-' '-'  */
#line 854 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).rel_pattern) = make_rel_pattern_varlen(NULL, NULL, NULL, false, false, NULL);
        }
#line 3485 "build/parser/cypher_gram.tab.c"
    break;

  case 126: /* variable_opt: %empty  */
#line 860 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).string) = NULL; }
#line 3491 "build/parser/cypher_gram.tab.c"
    break;

  case 127: /* variable_opt: IDENTIFIER  */
#line 861 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).string) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string); }
#line 3497 "build/parser/cypher_gram.tab.c"
    break;

  case 128: /* variable_opt: BQIDENT  */
#line 862 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).string) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string); }
#line 3503 "build/parser/cypher_gram.tab.c"
    break;

  case 129: /* variable_opt: END_P  */
#line 863 "src/backend/parser/cypher_gram.y"
                    { ((*yyvalp).string) = strdup("end"); }
#line 3509 "build/parser/cypher_gram.tab.c"
    break;

  case 130: /* varlen_range_opt: %empty  */
#line 869 "src/backend/parser/cypher_gram.y"
        { ((*yyvalp).varlen_range) = NULL; }
#line 3515 "build/parser/cypher_gram.tab.c"
    break;

  case 131: /* varlen_range_opt: '*'  */
#line 871 "src/backend/parser/cypher_gram.y"
        { ((*yyvalp).varlen_range) = make_varlen_range(1, -1); }
#line 3521 "build/parser/cypher_gram.tab.c"
    break;

  case 132: /* varlen_range_opt: '*' INTEGER  */
#line 873 "src/backend/parser/cypher_gram.y"
        { ((*yyvalp).varlen_range) = make_varlen_range((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.integer), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.integer)); }
#line 3527 "build/parser/cypher_gram.tab.c"
    break;

  case 133: /* varlen_range_opt: '*' INTEGER DOT_DOT INTEGER  */
#line 875 "src/backend/parser/cypher_gram.y"
        { ((*yyvalp).varlen_range) = make_varlen_range((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.integer), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.integer)); }
#line 3533 "build/parser/cypher_gram.tab.c"
    break;

  case 134: /* varlen_range_opt: '*' INTEGER DOT_DOT  */
#line 877 "src/backend/parser/cypher_gram.y"
        { ((*yyvalp).varlen_range) = make_varlen_range((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.integer), -1); }
#line 3539 "build/parser/cypher_gram.tab.c"
    break;

  case 135: /* varlen_range_opt: '*' DOT_DOT INTEGER  */
#line 879 "src/backend/parser/cypher_gram.y"
        { ((*yyvalp).varlen_range) = make_varlen_range(1, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.integer)); }
#line 3545 "build/parser/cypher_gram.tab.c"
    break;

  case 136: /* label_opt: %empty  */
#line 883 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).list) = NULL; }
#line 3551 "build/parser/cypher_gram.tab.c"
    break;

  case 137: /* label_opt: label_list  */
#line 884 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.list); }
#line 3557 "build/parser/cypher_gram.tab.c"
    break;

  case 138: /* label_list: ':' IDENTIFIER  */
#line 890 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *label = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)label);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3568 "build/parser/cypher_gram.tab.c"
    break;

  case 139: /* label_list: ':' BQIDENT  */
#line 897 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *label = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)label);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3579 "build/parser/cypher_gram.tab.c"
    break;

  case 140: /* label_list: label_list ':' IDENTIFIER  */
#line 904 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
            cypher_literal *label = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)label);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3590 "build/parser/cypher_gram.tab.c"
    break;

  case 141: /* label_list: label_list ':' BQIDENT  */
#line 911 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
            cypher_literal *label = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)label);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3601 "build/parser/cypher_gram.tab.c"
    break;

  case 142: /* rel_type_list: IDENTIFIER '|' IDENTIFIER  */
#line 921 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *type_lit1 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            cypher_literal *type_lit3 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit1);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit3);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3615 "build/parser/cypher_gram.tab.c"
    break;

  case 143: /* rel_type_list: IDENTIFIER '|' ':' IDENTIFIER  */
#line 931 "src/backend/parser/cypher_gram.y"
        {
            /* Support [:TYPE1|:TYPE2] syntax with colon before second type */
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *type_lit1 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            cypher_literal *type_lit4 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit1);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit4);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3630 "build/parser/cypher_gram.tab.c"
    break;

  case 144: /* rel_type_list: IDENTIFIER '|' BQIDENT  */
#line 942 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *type_lit1 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            cypher_literal *type_lit3 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit1);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit3);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3644 "build/parser/cypher_gram.tab.c"
    break;

  case 145: /* rel_type_list: IDENTIFIER '|' ':' BQIDENT  */
#line 952 "src/backend/parser/cypher_gram.y"
        {
            /* Support [:TYPE1|:`backtick-type`] syntax */
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *type_lit1 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            cypher_literal *type_lit4 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit1);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit4);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3659 "build/parser/cypher_gram.tab.c"
    break;

  case 146: /* rel_type_list: BQIDENT '|' IDENTIFIER  */
#line 963 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *type_lit1 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            cypher_literal *type_lit3 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit1);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit3);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3673 "build/parser/cypher_gram.tab.c"
    break;

  case 147: /* rel_type_list: BQIDENT '|' ':' IDENTIFIER  */
#line 973 "src/backend/parser/cypher_gram.y"
        {
            /* Support [:`backtick-type`|:TYPE2] syntax */
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *type_lit1 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            cypher_literal *type_lit4 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit1);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit4);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3688 "build/parser/cypher_gram.tab.c"
    break;

  case 148: /* rel_type_list: BQIDENT '|' BQIDENT  */
#line 984 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *type_lit1 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            cypher_literal *type_lit3 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit1);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit3);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3702 "build/parser/cypher_gram.tab.c"
    break;

  case 149: /* rel_type_list: BQIDENT '|' ':' BQIDENT  */
#line 994 "src/backend/parser/cypher_gram.y"
        {
            /* Support [:`backtick-type`|:`backtick-type2`] syntax */
            ((*yyvalp).list) = ast_list_create();
            cypher_literal *type_lit1 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            cypher_literal *type_lit4 = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit1);
            ast_list_append(((*yyvalp).list), (ast_node*)type_lit4);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3717 "build/parser/cypher_gram.tab.c"
    break;

  case 150: /* rel_type_list: rel_type_list '|' IDENTIFIER  */
#line 1005 "src/backend/parser/cypher_gram.y"
        {
            cypher_literal *type_lit = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)type_lit);
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3728 "build/parser/cypher_gram.tab.c"
    break;

  case 151: /* rel_type_list: rel_type_list '|' BQIDENT  */
#line 1012 "src/backend/parser/cypher_gram.y"
        {
            cypher_literal *type_lit = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)type_lit);
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3739 "build/parser/cypher_gram.tab.c"
    break;

  case 152: /* rel_type_list: rel_type_list '|' ':' IDENTIFIER  */
#line 1019 "src/backend/parser/cypher_gram.y"
        {
            cypher_literal *type_lit = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.list), (ast_node*)type_lit);
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.list);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3750 "build/parser/cypher_gram.tab.c"
    break;

  case 153: /* rel_type_list: rel_type_list '|' ':' BQIDENT  */
#line 1026 "src/backend/parser/cypher_gram.y"
        {
            cypher_literal *type_lit = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.list), (ast_node*)type_lit);
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.list);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3761 "build/parser/cypher_gram.tab.c"
    break;

  case 154: /* expr: primary_expr  */
#line 1036 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 3767 "build/parser/cypher_gram.tab.c"
    break;

  case 155: /* expr: '+' expr  */
#line 1037 "src/backend/parser/cypher_gram.y"
                                 { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 3773 "build/parser/cypher_gram.tab.c"
    break;

  case 156: /* expr: '-' expr  */
#line 1038 "src/backend/parser/cypher_gram.y"
                                  { 
        /* Handle unary minus */
        if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node)->type == AST_NODE_LITERAL) {
            cypher_literal *lit = (cypher_literal*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
            if (lit->literal_type == LITERAL_INTEGER) {
                lit->value.integer = -lit->value.integer;
                ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
            } else if (lit->literal_type == LITERAL_DECIMAL) {
                lit->value.decimal = -lit->value.decimal;
                ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
            } else {
                /* For other types, we'd need a unary minus node */
                ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
            }
        } else {
            /* For non-literals, we'd need a unary minus expression node */
            ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node);
        }
    }
#line 3797 "build/parser/cypher_gram.tab.c"
    break;

  case 157: /* expr: expr '+' expr  */
#line 1057 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_ADD, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3803 "build/parser/cypher_gram.tab.c"
    break;

  case 158: /* expr: expr '-' expr  */
#line 1058 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_SUB, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3809 "build/parser/cypher_gram.tab.c"
    break;

  case 159: /* expr: expr '*' expr  */
#line 1059 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_MUL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3815 "build/parser/cypher_gram.tab.c"
    break;

  case 160: /* expr: expr '/' expr  */
#line 1060 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_DIV, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3821 "build/parser/cypher_gram.tab.c"
    break;

  case 161: /* expr: expr '%' expr  */
#line 1061 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_MOD, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3827 "build/parser/cypher_gram.tab.c"
    break;

  case 162: /* expr: expr '=' expr  */
#line 1062 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_EQ, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3833 "build/parser/cypher_gram.tab.c"
    break;

  case 163: /* expr: expr NOT_EQ expr  */
#line 1063 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_NEQ, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3839 "build/parser/cypher_gram.tab.c"
    break;

  case 164: /* expr: expr '<' expr  */
#line 1064 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_LT, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3845 "build/parser/cypher_gram.tab.c"
    break;

  case 165: /* expr: expr '>' expr  */
#line 1065 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_GT, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3851 "build/parser/cypher_gram.tab.c"
    break;

  case 166: /* expr: expr LT_EQ expr  */
#line 1066 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_LTE, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3857 "build/parser/cypher_gram.tab.c"
    break;

  case 167: /* expr: expr GT_EQ expr  */
#line 1067 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_GTE, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3863 "build/parser/cypher_gram.tab.c"
    break;

  case 168: /* expr: expr REGEX_MATCH expr  */
#line 1068 "src/backend/parser/cypher_gram.y"
                            { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_REGEX_MATCH, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3869 "build/parser/cypher_gram.tab.c"
    break;

  case 169: /* expr: expr AND expr  */
#line 1069 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_AND, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3875 "build/parser/cypher_gram.tab.c"
    break;

  case 170: /* expr: expr OR expr  */
#line 1070 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_OR, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3881 "build/parser/cypher_gram.tab.c"
    break;

  case 171: /* expr: expr XOR expr  */
#line 1071 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_XOR, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3887 "build/parser/cypher_gram.tab.c"
    break;

  case 172: /* expr: expr IN expr  */
#line 1072 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_IN, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3893 "build/parser/cypher_gram.tab.c"
    break;

  case 173: /* expr: expr STARTS WITH expr  */
#line 1073 "src/backend/parser/cypher_gram.y"
                                         { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_STARTS_WITH, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line); }
#line 3899 "build/parser/cypher_gram.tab.c"
    break;

  case 174: /* expr: expr ENDS WITH expr  */
#line 1074 "src/backend/parser/cypher_gram.y"
                                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_ENDS_WITH, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line); }
#line 3905 "build/parser/cypher_gram.tab.c"
    break;

  case 175: /* expr: expr CONTAINS expr  */
#line 1075 "src/backend/parser/cypher_gram.y"
                                        { ((*yyvalp).node) = (ast_node*)make_binary_op(BINARY_OP_CONTAINS, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3911 "build/parser/cypher_gram.tab.c"
    break;

  case 176: /* expr: NOT expr  */
#line 1076 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)make_not_expr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3917 "build/parser/cypher_gram.tab.c"
    break;

  case 177: /* expr: expr IS NULL_P  */
#line 1077 "src/backend/parser/cypher_gram.y"
                          { ((*yyvalp).node) = (ast_node*)make_null_check((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line); }
#line 3923 "build/parser/cypher_gram.tab.c"
    break;

  case 178: /* expr: expr IS NOT NULL_P  */
#line 1078 "src/backend/parser/cypher_gram.y"
                          { ((*yyvalp).node) = (ast_node*)make_null_check((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), true, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line); }
#line 3929 "build/parser/cypher_gram.tab.c"
    break;

  case 179: /* expr: '(' expr ')'  */
#line 1079 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node); }
#line 3935 "build/parser/cypher_gram.tab.c"
    break;

  case 180: /* expr: node_pattern rel_pattern node_pattern  */
#line 1086 "src/backend/parser/cypher_gram.y"
        {
            /* Build a path from the pattern elements */
            ast_list *elements = ast_list_create();
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node_pattern));
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.rel_pattern));
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node_pattern));
            cypher_path *path = make_path(elements);
            /* Wrap in pattern list and create EXISTS expression */
            ast_list *pattern_list = ast_list_create();
            ast_list_append(pattern_list, (ast_node*)path);
            ((*yyvalp).node) = (ast_node*)make_exists_pattern_expr(pattern_list, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 3952 "build/parser/cypher_gram.tab.c"
    break;

  case 181: /* expr: node_pattern rel_pattern node_pattern rel_pattern node_pattern  */
#line 1099 "src/backend/parser/cypher_gram.y"
        {
            /* Chained pattern: (a)-[r1]->(b)-[r2]->(c) */
            ast_list *elements = ast_list_create();
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.node_pattern));
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.rel_pattern));
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node_pattern));
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.rel_pattern));
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node_pattern));
            cypher_path *path = make_path(elements);
            ast_list *pattern_list = ast_list_create();
            ast_list_append(pattern_list, (ast_node*)path);
            ((*yyvalp).node) = (ast_node*)make_exists_pattern_expr(pattern_list, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc).first_line);
        }
#line 3970 "build/parser/cypher_gram.tab.c"
    break;

  case 182: /* expr: expr '.' IDENTIFIER  */
#line 1113 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_property((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3979 "build/parser/cypher_gram.tab.c"
    break;

  case 183: /* expr: expr '.' BQIDENT  */
#line 1118 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_property((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 3988 "build/parser/cypher_gram.tab.c"
    break;

  case 184: /* expr: expr '[' expr ']'  */
#line 1123 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_subscript((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 3996 "build/parser/cypher_gram.tab.c"
    break;

  case 185: /* expr: expr '[' expr DOT_DOT expr ']'  */
#line 1127 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_slice((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc).first_line);
        }
#line 4004 "build/parser/cypher_gram.tab.c"
    break;

  case 186: /* expr: expr '[' expr DOT_DOT ']'  */
#line 1131 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_slice((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
        }
#line 4012 "build/parser/cypher_gram.tab.c"
    break;

  case 187: /* expr: expr '[' DOT_DOT expr ']'  */
#line 1135 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_slice((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.node), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
        }
#line 4020 "build/parser/cypher_gram.tab.c"
    break;

  case 188: /* primary_expr: literal_expr  */
#line 1141 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4026 "build/parser/cypher_gram.tab.c"
    break;

  case 189: /* primary_expr: identifier  */
#line 1142 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.identifier); }
#line 4032 "build/parser/cypher_gram.tab.c"
    break;

  case 190: /* primary_expr: parameter  */
#line 1143 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.parameter); }
#line 4038 "build/parser/cypher_gram.tab.c"
    break;

  case 191: /* primary_expr: function_call  */
#line 1144 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4044 "build/parser/cypher_gram.tab.c"
    break;

  case 192: /* primary_expr: list_predicate  */
#line 1145 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4050 "build/parser/cypher_gram.tab.c"
    break;

  case 193: /* primary_expr: reduce_expr  */
#line 1146 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4056 "build/parser/cypher_gram.tab.c"
    break;

  case 194: /* primary_expr: list_literal  */
#line 1147 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4062 "build/parser/cypher_gram.tab.c"
    break;

  case 195: /* primary_expr: list_comprehension  */
#line 1148 "src/backend/parser/cypher_gram.y"
                         { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4068 "build/parser/cypher_gram.tab.c"
    break;

  case 196: /* primary_expr: pattern_comprehension  */
#line 1149 "src/backend/parser/cypher_gram.y"
                            { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4074 "build/parser/cypher_gram.tab.c"
    break;

  case 197: /* primary_expr: map_literal  */
#line 1150 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4080 "build/parser/cypher_gram.tab.c"
    break;

  case 198: /* primary_expr: map_projection  */
#line 1151 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4086 "build/parser/cypher_gram.tab.c"
    break;

  case 199: /* primary_expr: case_expression  */
#line 1152 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node); }
#line 4092 "build/parser/cypher_gram.tab.c"
    break;

  case 200: /* primary_expr: IDENTIFIER ':' IDENTIFIER  */
#line 1154 "src/backend/parser/cypher_gram.y"
        {
            cypher_identifier *base = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            ((*yyvalp).node) = (ast_node*)make_label_expr((ast_node*)base, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 4103 "build/parser/cypher_gram.tab.c"
    break;

  case 201: /* literal_expr: literal  */
#line 1163 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).node) = (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.literal); }
#line 4109 "build/parser/cypher_gram.tab.c"
    break;

  case 202: /* function_call: IDENTIFIER '(' ')'  */
#line 1168 "src/backend/parser/cypher_gram.y"
        {
            /* Check if this is EXISTS function call */
            if (strcasecmp((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), "exists") == 0) {
                /* Empty EXISTS() - invalid */
                free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
                cypher_yyerror(&(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc), context, "EXISTS requires an argument");
                YYERROR;
            } else {
                ast_list *args = ast_list_create();
                ((*yyvalp).node) = (ast_node*)make_function_call((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), args, false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
                free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
            }
        }
#line 4127 "build/parser/cypher_gram.tab.c"
    break;

  case 203: /* function_call: IDENTIFIER '(' argument_list ')'  */
#line 1183 "src/backend/parser/cypher_gram.y"
        {
            /* Check if this is EXISTS function call */
            if (strcasecmp((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), "exists") == 0) {
                /* EXISTS with argument list - check first arg */
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list)->count == 1 && (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list)->items[0] != NULL) {
                    ast_node *arg = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list)->items[0];
                    if (arg->type == AST_NODE_PROPERTY) {
                        ((*yyvalp).node) = (ast_node*)make_exists_property_expr(arg, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
                        (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list)->items[0] = NULL;  /* Transfer ownership */
                        ast_list_free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list));
                    } else {
                        ((*yyvalp).node) = (ast_node*)make_exists_pattern_expr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
                    }
                } else {
                    cypher_yyerror(&(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc), context, "EXISTS requires exactly one argument");
                    ast_list_free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list));
                    free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
                    YYERROR;
                }
                free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
            } else {
                ((*yyvalp).node) = (ast_node*)make_function_call((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
                free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
            }
        }
#line 4157 "build/parser/cypher_gram.tab.c"
    break;

  case 204: /* function_call: IDENTIFIER '(' DISTINCT expr ')'  */
#line 1209 "src/backend/parser/cypher_gram.y"
        {
            ast_list *args = ast_list_create();
            ast_list_append(args, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node));
            ((*yyvalp).node) = (ast_node*)make_function_call((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string), args, true, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.string));
        }
#line 4168 "build/parser/cypher_gram.tab.c"
    break;

  case 205: /* function_call: IDENTIFIER '(' '*' ')'  */
#line 1216 "src/backend/parser/cypher_gram.y"
        {
            ast_list *args = ast_list_create();
            /* For count(*), we'll use a special NULL argument to indicate * */
            ast_list_append(args, NULL);
            ((*yyvalp).node) = (ast_node*)make_function_call((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), args, false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
        }
#line 4180 "build/parser/cypher_gram.tab.c"
    break;

  case 206: /* function_call: EXISTS '(' pattern_list ')'  */
#line 1224 "src/backend/parser/cypher_gram.y"
        {
            /* EXISTS((pattern)) - check for relationship/path existence */
            ((*yyvalp).node) = (ast_node*)make_exists_pattern_expr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
        }
#line 4189 "build/parser/cypher_gram.tab.c"
    break;

  case 207: /* function_call: EXISTS '(' IDENTIFIER '.' IDENTIFIER ')'  */
#line 1229 "src/backend/parser/cypher_gram.y"
        {
            /* EXISTS(n.property) - unambiguous property existence check */
            ast_node *var = (ast_node*)make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            ast_node *prop = (ast_node*)make_property(var, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc).first_line);
            ((*yyvalp).node) = (ast_node*)make_exists_property_expr(prop, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.string));
        }
#line 4202 "build/parser/cypher_gram.tab.c"
    break;

  case 208: /* function_call: CONTAINS '(' argument_list ')'  */
#line 1239 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_function_call(strdup("contains"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
        }
#line 4210 "build/parser/cypher_gram.tab.c"
    break;

  case 209: /* function_call: STARTS '(' argument_list ')'  */
#line 1243 "src/backend/parser/cypher_gram.y"
        {
            /* startsWith function uses STARTS keyword */
            ((*yyvalp).node) = (ast_node*)make_function_call(strdup("startsWith"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
        }
#line 4219 "build/parser/cypher_gram.tab.c"
    break;

  case 210: /* function_call: ENDS '(' argument_list ')'  */
#line 1248 "src/backend/parser/cypher_gram.y"
        {
            /* endsWith function uses ENDS keyword */
            ((*yyvalp).node) = (ast_node*)make_function_call(strdup("endsWith"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
        }
#line 4228 "build/parser/cypher_gram.tab.c"
    break;

  case 211: /* list_predicate: ALL '(' IDENTIFIER IN expr WHERE expr ')'  */
#line 1257 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_list_predicate(LIST_PRED_ALL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 4237 "build/parser/cypher_gram.tab.c"
    break;

  case 212: /* list_predicate: ANY '(' IDENTIFIER IN expr WHERE expr ')'  */
#line 1262 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_list_predicate(LIST_PRED_ANY, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 4246 "build/parser/cypher_gram.tab.c"
    break;

  case 213: /* list_predicate: NONE '(' IDENTIFIER IN expr WHERE expr ')'  */
#line 1267 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_list_predicate(LIST_PRED_NONE, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 4255 "build/parser/cypher_gram.tab.c"
    break;

  case 214: /* list_predicate: SINGLE '(' IDENTIFIER IN expr WHERE expr ')'  */
#line 1272 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_list_predicate(LIST_PRED_SINGLE, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 4264 "build/parser/cypher_gram.tab.c"
    break;

  case 215: /* reduce_expr: REDUCE '(' IDENTIFIER '=' expr ',' IDENTIFIER IN expr '|' expr ')'  */
#line 1281 "src/backend/parser/cypher_gram.y"
        {
            /* reduce(acc = initial, x IN list | expression) */
            ((*yyvalp).node) = (ast_node*)make_reduce_expr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-11)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 4275 "build/parser/cypher_gram.tab.c"
    break;

  case 216: /* argument_list: expr  */
#line 1292 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 4284 "build/parser/cypher_gram.tab.c"
    break;

  case 217: /* argument_list: argument_list ',' expr  */
#line 1297 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
        }
#line 4293 "build/parser/cypher_gram.tab.c"
    break;

  case 218: /* list_literal: '[' ']'  */
#line 1306 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_list(ast_list_create(), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line);
        }
#line 4301 "build/parser/cypher_gram.tab.c"
    break;

  case 219: /* list_literal: '[' return_item_list ']'  */
#line 1310 "src/backend/parser/cypher_gram.y"
        {
            /* Reuse return_item_list for comma-separated expressions */
            /* But we need to extract the expressions from return_items */
            ast_list *exprs = ast_list_create();
            for (int i = 0; i < (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list)->count; i++) {
                cypher_return_item *item = (cypher_return_item*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list)->items[i];
                ast_list_append(exprs, item->expr);
                item->expr = NULL;  /* Prevent double-free */
            }
            ast_list_free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list));
            ((*yyvalp).node) = (ast_node*)make_list(exprs, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4318 "build/parser/cypher_gram.tab.c"
    break;

  case 220: /* list_comprehension: '[' IDENTIFIER IN expr ']'  */
#line 1327 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_list_comprehension((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), NULL, NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
        }
#line 4327 "build/parser/cypher_gram.tab.c"
    break;

  case 221: /* list_comprehension: '[' IDENTIFIER IN expr WHERE expr ']'  */
#line 1332 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_list_comprehension((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 4336 "build/parser/cypher_gram.tab.c"
    break;

  case 222: /* list_comprehension: '[' IDENTIFIER IN expr '|' expr ']'  */
#line 1337 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_list_comprehension((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.string));
        }
#line 4345 "build/parser/cypher_gram.tab.c"
    break;

  case 223: /* list_comprehension: '[' IDENTIFIER IN expr WHERE expr '|' expr ']'  */
#line 1342 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_list_comprehension((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval.string));
        }
#line 4354 "build/parser/cypher_gram.tab.c"
    break;

  case 224: /* pattern_comprehension: '[' '(' variable_opt label_opt properties_opt ')' rel_pattern node_pattern '|' expr ']'  */
#line 1359 "src/backend/parser/cypher_gram.y"
        {
            cypher_node_pattern *first = make_node_pattern((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-7)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.map));
            ast_list *elements = ast_list_create();
            ast_list_append(elements, (ast_node*)first);
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.rel_pattern));
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node_pattern));
            cypher_path *path = make_path(elements);

            ast_list *pattern = ast_list_create();
            ast_list_append(pattern, (ast_node*)path);
            ((*yyvalp).node) = (ast_node*)make_pattern_comprehension(pattern, NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yyloc).first_line);
        }
#line 4371 "build/parser/cypher_gram.tab.c"
    break;

  case 225: /* pattern_comprehension: '[' '(' variable_opt label_opt properties_opt ')' rel_pattern node_pattern WHERE expr '|' expr ']'  */
#line 1372 "src/backend/parser/cypher_gram.y"
        {
            cypher_node_pattern *first = make_node_pattern((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-10)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-9)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-8)].yystate.yysemantics.yyval.map));
            ast_list *elements = ast_list_create();
            ast_list_append(elements, (ast_node*)first);
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-6)].yystate.yysemantics.yyval.rel_pattern));
            ast_list_append(elements, (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yysemantics.yyval.node_pattern));
            cypher_path *path = make_path(elements);

            ast_list *pattern = ast_list_create();
            ast_list_append(pattern, (ast_node*)path);
            ((*yyvalp).node) = (ast_node*)make_pattern_comprehension(pattern, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-12)].yystate.yyloc).first_line);
        }
#line 4388 "build/parser/cypher_gram.tab.c"
    break;

  case 226: /* map_literal: '{' '}'  */
#line 1389 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_map(ast_list_create(), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line);
        }
#line 4396 "build/parser/cypher_gram.tab.c"
    break;

  case 227: /* map_literal: '{' map_pair_list '}'  */
#line 1393 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_map((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4404 "build/parser/cypher_gram.tab.c"
    break;

  case 228: /* map_projection: IDENTIFIER '{' map_projection_list '}'  */
#line 1401 "src/backend/parser/cypher_gram.y"
        {
            cypher_identifier *base = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            ((*yyvalp).node) = (ast_node*)make_map_projection((ast_node*)base, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
        }
#line 4414 "build/parser/cypher_gram.tab.c"
    break;

  case 229: /* map_projection_list: map_projection_item  */
#line 1410 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 4423 "build/parser/cypher_gram.tab.c"
    break;

  case 230: /* map_projection_list: map_projection_list ',' map_projection_item  */
#line 1415 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
        }
#line 4432 "build/parser/cypher_gram.tab.c"
    break;

  case 231: /* map_projection_item: '.' IDENTIFIER  */
#line 1423 "src/backend/parser/cypher_gram.y"
        {
            /* Shorthand: .prop -> key=prop, property=prop, expr=NULL */
            ((*yyvalp).node) = (ast_node*)make_map_projection_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 4442 "build/parser/cypher_gram.tab.c"
    break;

  case 232: /* map_projection_item: '.' '*'  */
#line 1429 "src/backend/parser/cypher_gram.y"
        {
            /* All properties: .* -> key=NULL, property="*", expr=NULL */
            ((*yyvalp).node) = (ast_node*)make_map_projection_item(NULL, strdup("*"), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yyloc).first_line);
        }
#line 4451 "build/parser/cypher_gram.tab.c"
    break;

  case 233: /* map_projection_item: IDENTIFIER ':' '.' IDENTIFIER  */
#line 1434 "src/backend/parser/cypher_gram.y"
        {
            /* Aliased property: alias: .prop */
            ((*yyvalp).node) = (ast_node*)make_map_projection_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.string));
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 4462 "build/parser/cypher_gram.tab.c"
    break;

  case 234: /* map_projection_item: IDENTIFIER ':' expr  */
#line 1441 "src/backend/parser/cypher_gram.y"
        {
            /* Computed value: alias: expr */
            ((*yyvalp).node) = (ast_node*)make_map_projection_item((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string));
        }
#line 4472 "build/parser/cypher_gram.tab.c"
    break;

  case 235: /* case_expression: CASE when_clause_list END_P  */
#line 1455 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_case_expr(NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4480 "build/parser/cypher_gram.tab.c"
    break;

  case 236: /* case_expression: CASE when_clause_list ELSE expr END_P  */
#line 1459 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_case_expr(NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yyloc).first_line);
        }
#line 4488 "build/parser/cypher_gram.tab.c"
    break;

  case 237: /* case_expression: CASE expr when_clause_list END_P  */
#line 1464 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_case_expr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), NULL, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
        }
#line 4496 "build/parser/cypher_gram.tab.c"
    break;

  case 238: /* case_expression: CASE expr when_clause_list ELSE expr END_P  */
#line 1468 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_case_expr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-5)].yystate.yyloc).first_line);
        }
#line 4504 "build/parser/cypher_gram.tab.c"
    break;

  case 239: /* when_clause_list: when_clause  */
#line 1475 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
        }
#line 4513 "build/parser/cypher_gram.tab.c"
    break;

  case 240: /* when_clause_list: when_clause_list when_clause  */
#line 1480 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list);
        }
#line 4522 "build/parser/cypher_gram.tab.c"
    break;

  case 241: /* when_clause: WHEN expr THEN expr  */
#line 1488 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).node) = (ast_node*)make_when_clause((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yyloc).first_line);
        }
#line 4530 "build/parser/cypher_gram.tab.c"
    break;

  case 242: /* literal: INTEGER  */
#line 1495 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).literal) = make_integer_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.integer), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
        }
#line 4538 "build/parser/cypher_gram.tab.c"
    break;

  case 243: /* literal: DECIMAL  */
#line 1499 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).literal) = make_decimal_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.decimal), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
        }
#line 4546 "build/parser/cypher_gram.tab.c"
    break;

  case 244: /* literal: STRING  */
#line 1503 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).literal) = make_string_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 4555 "build/parser/cypher_gram.tab.c"
    break;

  case 245: /* literal: TRUE_P  */
#line 1508 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).literal) = make_boolean_literal(true, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
        }
#line 4563 "build/parser/cypher_gram.tab.c"
    break;

  case 246: /* literal: FALSE_P  */
#line 1512 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).literal) = make_boolean_literal(false, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
        }
#line 4571 "build/parser/cypher_gram.tab.c"
    break;

  case 247: /* literal: NULL_P  */
#line 1516 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).literal) = make_null_literal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
        }
#line 4579 "build/parser/cypher_gram.tab.c"
    break;

  case 248: /* identifier: IDENTIFIER  */
#line 1523 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).identifier) = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 4588 "build/parser/cypher_gram.tab.c"
    break;

  case 249: /* identifier: BQIDENT  */
#line 1528 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).identifier) = make_identifier((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 4597 "build/parser/cypher_gram.tab.c"
    break;

  case 250: /* identifier: END_P  */
#line 1533 "src/backend/parser/cypher_gram.y"
        {
            /* Allow 'end' as an identifier - it's only reserved in CASE...END context */
            ((*yyvalp).identifier) = make_identifier(strdup("end"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
        }
#line 4606 "build/parser/cypher_gram.tab.c"
    break;

  case 251: /* parameter: PARAMETER  */
#line 1541 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).parameter) = make_parameter((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yyloc).first_line);
            free((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.string));
        }
#line 4615 "build/parser/cypher_gram.tab.c"
    break;

  case 252: /* properties_opt: %empty  */
#line 1549 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).map) = NULL; }
#line 4621 "build/parser/cypher_gram.tab.c"
    break;

  case 253: /* properties_opt: '{' '}'  */
#line 1550 "src/backend/parser/cypher_gram.y"
                        { ((*yyvalp).map) = NULL; }
#line 4627 "build/parser/cypher_gram.tab.c"
    break;

  case 254: /* properties_opt: '{' map_pair_list '}'  */
#line 1552 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).map) = make_map((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yyval.list), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4635 "build/parser/cypher_gram.tab.c"
    break;

  case 255: /* map_pair_list: map_pair  */
#line 1559 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).list) = ast_list_create();
            ast_list_append(((*yyvalp).list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.map_pair));
        }
#line 4644 "build/parser/cypher_gram.tab.c"
    break;

  case 256: /* map_pair_list: map_pair_list ',' map_pair  */
#line 1564 "src/backend/parser/cypher_gram.y"
        {
            ast_list_append((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list), (ast_node*)(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.map_pair));
            ((*yyvalp).list) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.list);
        }
#line 4653 "build/parser/cypher_gram.tab.c"
    break;

  case 257: /* map_pair: IDENTIFIER ':' expr  */
#line 1572 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).map_pair) = make_map_pair((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4661 "build/parser/cypher_gram.tab.c"
    break;

  case 258: /* map_pair: BQIDENT ':' expr  */
#line 1576 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).map_pair) = make_map_pair((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4669 "build/parser/cypher_gram.tab.c"
    break;

  case 259: /* map_pair: STRING ':' expr  */
#line 1580 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).map_pair) = make_map_pair((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yyval.string), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4677 "build/parser/cypher_gram.tab.c"
    break;

  case 260: /* map_pair: ASC ':' expr  */
#line 1584 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).map_pair) = make_map_pair("asc", (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4685 "build/parser/cypher_gram.tab.c"
    break;

  case 261: /* map_pair: DESC ':' expr  */
#line 1588 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).map_pair) = make_map_pair("desc", (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4693 "build/parser/cypher_gram.tab.c"
    break;

  case 262: /* map_pair: ORDER ':' expr  */
#line 1592 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).map_pair) = make_map_pair("order", (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4701 "build/parser/cypher_gram.tab.c"
    break;

  case 263: /* map_pair: BY ':' expr  */
#line 1596 "src/backend/parser/cypher_gram.y"
        {
            ((*yyvalp).map_pair) = make_map_pair("by", (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yyval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yyloc).first_line);
        }
#line 4709 "build/parser/cypher_gram.tab.c"
    break;


#line 4713 "build/parser/cypher_gram.tab.c"

      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yylhsNonterm (yyrule), yyvalp, yylocp);

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYNOMEM
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YY_USE (yy0);
  YY_USE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, cypher_parser_context *context)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (context);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys, cypher_parser_context *context)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yy_accessing_symbol (yys->yylrState),
                &yys->yysemantics.yyval, &yys->yyloc, context);
  else
    {
#if CYPHER_YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YY_FPRINTF ((stderr, "%s unresolved", yymsg));
          else
            YY_FPRINTF ((stderr, "%s incomplete", yymsg));
          YY_SYMBOL_PRINT ("", yy_accessing_symbol (yys->yylrState), YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh, context);
        }
    }
}

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yy_state_t yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yy_state_t yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yyn) \
  0

/** The action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline int
yygetLRActions (yy_state_t yystate, yysymbol_kind_t yytoken, const short** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yytoken == YYSYMBOL_YYerror)
    {
      // This is the error token.
      *yyconflicts = yyconfl;
      return 0;
    }
  else if (yyisDefaultedState (yystate)
           || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyconflicts = yyconfl;
      return -yydefact[yystate];
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return yytable[yyindex];
    }
  else
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return 0;
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yy_state_t
yyLRgotoState (yy_state_t yystate, yysymbol_kind_t yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YY_ASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
      yynewOption->yyloc = yylloc;
    }
  else
    yynewOption->yyrawchar = CYPHER_CYPHER_YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates
    = YY_CAST (yyGLRState**,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yystates[0]));
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds
    = YY_CAST (yybool*,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yylookaheadNeeds[0]));
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  memset (yyset->yylookaheadNeeds,
          0,
          YY_CAST (YYSIZE_T, yyset->yycapacity) * sizeof yyset->yylookaheadNeeds[0]);
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, YYPTRDIFF_T yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yysize)
                         * sizeof yystackp->yynextFree[0]));
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS, YYTOITEMS, YYX, YYTYPE)                   \
  &((YYTOITEMS)                                                         \
    - ((YYFROMITEMS) - YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX))))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  YYPTRDIFF_T yynewSize;
  YYPTRDIFF_T yyn;
  YYPTRDIFF_T yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yynewSize)
                         * sizeof yynewItems[0]));
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*YY_REINTERPRET_CAST (yybool *, yyp0))
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YY_DPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  YYPTRDIFF_T yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            YY_DPRINTF ((stderr, "Removing dead stacks.\n"));
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            YY_DPRINTF ((stderr, "Rename stack %ld -> %ld.\n",
                        YY_CAST (long, yyi), YY_CAST (long, yyj)));
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
            YYPTRDIFF_T yyposn,
            YYSTYPE* yyvalp, YYLTYPE* yylocp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyval = *yyvalp;
  yynewState->yyloc = *yylocp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
                 YYPTRDIFF_T yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YY_ASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if CYPHER_YYDEBUG

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, YYPTRDIFF_T yyk,
                 yyRuleNum yyrule, cypher_parser_context *context)
{
  int yynrhs = yyrhsLength (yyrule);
  int yylow = 1;
  int yyi;
  YY_FPRINTF ((stderr, "Reducing stack %ld by rule %d (line %d):\n",
               YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule]));
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YY_FPRINTF ((stderr, "   $%d = ", yyi + 1));
      yy_symbol_print (stderr,
                       yy_accessing_symbol (yyvsp[yyi - yynrhs + 1].yystate.yylrState),
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yyval,
                       &(YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL ((yyi + 1) - (yynrhs))].yystate.yyloc)                       , context);
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YY_FPRINTF ((stderr, " (unresolved)"));
      YY_FPRINTF ((stderr, "\n"));
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, YYLTYPE *yylocp, cypher_parser_context *context)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs
        = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yytops.yystates[yyk]);
      YY_ASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp, yyk,
                           yyvalp, yylocp, context);
    }
  else
    {
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yyGLRState* yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      int yyi;
      if (yynrhs == 0)
        /* Set default location.  */
        yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yys->yyloc;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyk, yyvalp, yylocp, context);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
             yybool yyforceEval, cypher_parser_context *context)
{
  YYPTRDIFF_T yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yyval;
      YYLTYPE yyloc;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yyval, &yyloc, context);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        YY_DPRINTF ((stderr,
                     "Parse on stack %ld rejected by rule %d (line %d).\n",
                     YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule]));
      if (yyflag != yyok)
        return yyflag;
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yyval, &yyloc);
    }
  else
    {
      YYPTRDIFF_T yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yy_state_t yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YY_DPRINTF ((stderr,
                   "Reduced stack %ld by rule %d (line %d); action deferred.  "
                   "Now in state %d.\n",
                   YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule],
                   yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YY_DPRINTF ((stderr, "Merging stack %ld into stack %ld.\n",
                                 YY_CAST (long, yyk), YY_CAST (long, yyi)));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static YYPTRDIFF_T
yysplitStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YY_ASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yycapacity <= yystackp->yytops.yysize)
    {
      YYPTRDIFF_T state_size = YYSIZEOF (yystackp->yytops.yystates[0]);
      YYPTRDIFF_T half_max_capacity = YYSIZE_MAXIMUM / 2 / state_size;
      if (half_max_capacity < yystackp->yytops.yycapacity)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      {
        yyGLRState** yynewStates
          = YY_CAST (yyGLRState**,
                     YYREALLOC (yystackp->yytops.yystates,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewStates[0])));
        if (yynewStates == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yystates = yynewStates;
      }

      {
        yybool* yynewLookaheadNeeds
          = YY_CAST (yybool*,
                     YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewLookaheadNeeds[0])));
        if (yynewLookaheadNeeds == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
      }
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize - 1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       0 < yyn;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yyval = yys0->yysemantics.yyval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yyval = yys1->yysemantics.yyval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, cypher_parser_context *context);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp, cypher_parser_context *context)
{
  if (0 < yyn)
    {
      YY_ASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp, context));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp, context));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, YYLTYPE *yylocp, cypher_parser_context *context)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp, context);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys, context);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  if (yynrhs == 0)
    /* Set default location.  */
    yyrhsVals[YYMAXRHS + YYMAXLEFT - 1].yystate.yyloc = yyopt->yystate->yyloc;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    YYLTYPE yylloc_current = yylloc;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yylloc = yyopt->yyloc;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, -1, yyvalp, yylocp, context);
    yychar = yychar_current;
    yylval = yylval_current;
    yylloc = yylloc_current;
  }
  return yyflag;
}

#if CYPHER_YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, empty>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1));
  else
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, tokens %ld .. %ld>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1, YY_CAST (long, yys->yyposn + 1),
                 YY_CAST (long, yyx->yystate->yyposn)));
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YY_FPRINTF ((stderr, "%*s%s <empty>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState))));
          else
            YY_FPRINTF ((stderr, "%*s%s <tokens %ld .. %ld>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState)),
                         YY_CAST (long, yystates[yyi-1]->yyposn + 1),
                         YY_CAST (long, yystates[yyi]->yyposn)));
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1, YYLTYPE *yylocp, cypher_parser_context *context)
{
  YY_USE (yyx0);
  YY_USE (yyx1);

#if CYPHER_YYDEBUG
  YY_FPRINTF ((stderr, "Ambiguity detected.\n"));
  YY_FPRINTF ((stderr, "Option 1,\n"));
  yyreportTree (yyx0, 2);
  YY_FPRINTF ((stderr, "\nOption 2,\n"));
  yyreportTree (yyx1, 2);
  YY_FPRINTF ((stderr, "\n"));
#endif

  yyerror (yylocp, context, YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the locations for each of the YYN1 states in *YYSTACKP,
 *  ending at YYS1.  Has no effect on previously resolved states.
 *  The first semantic option of a state is always chosen.  */
static void
yyresolveLocations (yyGLRState *yys1, int yyn1,
                    yyGLRStack *yystackp, cypher_parser_context *context)
{
  if (0 < yyn1)
    {
      yyresolveLocations (yys1->yypred, yyn1 - 1, yystackp, context);
      if (!yys1->yyresolved)
        {
          yyGLRStackItem yyrhsloc[1 + YYMAXRHS];
          int yynrhs;
          yySemanticOption *yyoption = yys1->yysemantics.yyfirstVal;
          YY_ASSERT (yyoption);
          yynrhs = yyrhsLength (yyoption->yyrule);
          if (0 < yynrhs)
            {
              yyGLRState *yys;
              int yyn;
              yyresolveLocations (yyoption->yystate, yynrhs,
                                  yystackp, context);
              for (yys = yyoption->yystate, yyn = yynrhs;
                   yyn > 0;
                   yys = yys->yypred, yyn -= 1)
                yyrhsloc[yyn].yystate.yyloc = yys->yyloc;
            }
          else
            {
              /* Both yyresolveAction and yyresolveLocations traverse the GSS
                 in reverse rightmost order.  It is only necessary to invoke
                 yyresolveLocations on a subforest for which yyresolveAction
                 would have been invoked next had an ambiguity not been
                 detected.  Thus the location of the previous state (but not
                 necessarily the previous state itself) is guaranteed to be
                 resolved already.  */
              yyGLRState *yyprevious = yyoption->yystate;
              yyrhsloc[0].yystate.yyloc = yyprevious->yyloc;
            }
          YYLLOC_DEFAULT ((yys1->yyloc), yyrhsloc, yynrhs);
        }
    }
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, cypher_parser_context *context)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yyval;
  YYRESULTTAG yyflag;
  YYLTYPE *yylocp = &yys->yyloc;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              yyresolveLocations (yys, 1, yystackp, context);
              return yyreportAmbiguity (yybest, yyp, yylocp, context);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YY_ASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yyval, yylocp, context);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yyval_other;
                YYLTYPE yydummy;
                yyflag = yyresolveAction (yyp, yystackp, &yyval_other, &yydummy, context);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yy_accessing_symbol (yys->yylrState),
                                &yyval, yylocp, context);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yyval, &yyval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yyval, yylocp, context);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yyval = yyval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp, cypher_parser_context *context)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             , context));
    }
  return yyok;
}

/** Called when returning to deterministic operation to clean up the extra
 * stacks. */
static void
yycompressStack (yyGLRStack* yystackp)
{
  /* yyr is the state after the split point.  */
  yyGLRState *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  {
    yyGLRState *yyp, *yyq;
    for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
         yyp != yystackp->yysplitPoint;
         yyr = yyp, yyp = yyq, yyq = yyp->yypred)
      yyp->yypred = yyr;
  }

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk,
                   YYPTRDIFF_T yyposn, YYLTYPE *yylocp, cypher_parser_context *context)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yy_state_t yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YY_DPRINTF ((stderr, "Stack %ld Entering state %d\n",
                   YY_CAST (long, yyk), yystate));

      YY_ASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule], context);
          if (yyflag == yyerr)
            {
              YY_DPRINTF ((stderr,
                           "Stack %ld dies "
                           "(predicate failure or explicit user error).\n",
                           YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yysymbol_kind_t yytoken = yygetToken (&yychar, yystackp, context);
          const short* yyconflicts;
          const int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;

          for (/* nothing */; *yyconflicts; yyconflicts += 1)
            {
              YYRESULTTAG yyflag;
              YYPTRDIFF_T yynewStack = yysplitStack (yystackp, yyk);
              YY_DPRINTF ((stderr, "Splitting off stack %ld from %ld.\n",
                           YY_CAST (long, yynewStack), YY_CAST (long, yyk)));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts], context);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn, yylocp, context));
              else if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yynewStack)));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction], context);
              if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr,
                               "Stack %ld dies "
                               "(predicate failure or explicit user error).\n",
                               YY_CAST (long, yyk)));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYSTACKP, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  */
static int
yypcontext_expected_tokens (const yyGLRStack* yystackp,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}

static int
yy_syntax_error_arguments (const yyGLRStack* yystackp,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  yysymbol_kind_t yytoken = yychar == CYPHER_CYPHER_YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yystackp,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}



static void
yyreportSyntaxError (yyGLRStack* yystackp, cypher_parser_context *context)
{
  if (yystackp->yyerrState != 0)
    return;
  {
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULLPTR;
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount
    = yy_syntax_error_arguments (yystackp, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    yyMemoryExhausted (yystackp);

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysz
          = yystrlen (yysymbol_name (yyarg[yyi]));
        if (YYSIZE_MAXIMUM - yysize < yysz)
          yysize_overflow = yytrue;
        else
          yysize += yysz;
      }
  }

  if (!yysize_overflow)
    yymsg = YY_CAST (char *, YYMALLOC (YY_CAST (YYSIZE_T, yysize)));

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
          if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
              yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
              yyformat += 2;
            }
          else
            {
              ++yyp;
              ++yyformat;
            }
        }
      yyerror (&yylloc, context, yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (&yylloc, context, YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp, cypher_parser_context *context)
{
  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yysymbol_kind_t yytoken;
        int yyj;
        if (yychar == CYPHER_YYEOF)
          yyFail (yystackp, &yylloc, context, YY_NULLPTR);
        if (yychar != CYPHER_CYPHER_YYEMPTY)
          {
            /* We throw away the lookahead, but the error range
               of the shifted error token must take it into account.  */
            yyGLRState *yys = yystackp->yytops.yystates[0];
            yyGLRStackItem yyerror_range[3];
            yyerror_range[1].yystate.yyloc = yys->yyloc;
            yyerror_range[2].yystate.yyloc = yylloc;
            YYLLOC_DEFAULT ((yys->yyloc), yyerror_range, 2);
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, &yylloc, context);
            yychar = CYPHER_CYPHER_YYEMPTY;
          }
        yytoken = yygetToken (&yychar, yystackp, context);
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  {
    YYPTRDIFF_T yyk;
    for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
      if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
        break;
    if (yyk >= yystackp->yytops.yysize)
      yyFail (yystackp, &yylloc, context, YY_NULLPTR);
    for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
      yymarkStackDeleted (yystackp, yyk);
    yyremoveDeletes (yystackp);
    yycompressStack (yystackp);
  }

  /* Pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      int yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYSYMBOL_YYerror;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYSYMBOL_YYerror
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              int yyaction = yytable[yyj];
              /* First adjust its location.*/
              YYLTYPE yyerrloc;
              yystackp->yyerror_range[2].yystate.yyloc = yylloc;
              YYLLOC_DEFAULT (yyerrloc, (yystackp->yyerror_range), 2);
              YY_SYMBOL_PRINT ("Shifting", yy_accessing_symbol (yyaction),
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yyaction,
                          yys->yyposn, &yylval, &yyerrloc);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      yystackp->yyerror_range[1].yystate.yyloc = yys->yyloc;
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys, context);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, &yylloc, context, YY_NULLPTR);
}

#define YYCHK1(YYE)                             \
  do {                                          \
    switch (YYE) {                              \
    case yyok:     break;                       \
    case yyabort:  goto yyabortlab;             \
    case yyaccept: goto yyacceptlab;            \
    case yyerr:    goto yyuser_error;           \
    case yynomem:  goto yyexhaustedlab;         \
    default:       goto yybuglab;               \
    }                                           \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (cypher_parser_context *context)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  YYPTRDIFF_T yyposn;

  YY_DPRINTF ((stderr, "Starting parse\n"));

  yychar = CYPHER_CYPHER_YYEMPTY;
  yylval = yyval_default;
  yylloc = yyloc_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval, &yylloc);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode. */
      while (yytrue)
        {
          yy_state_t yystate = yystack.yytops.yystates[0]->yylrState;
          YY_DPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyRuleNum yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  yyreportSyntaxError (&yystack, context);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue, context));
            }
          else
            {
              yysymbol_kind_t yytoken = yygetToken (&yychar, yystackp, context);
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
              if (*yyconflicts)
                /* Enter nondeterministic mode.  */
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = CYPHER_CYPHER_YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval, &yylloc);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
                  yystack.yyerror_range[1].yystate.yyloc = yylloc;
                  /* Issue an error message unless the scanner already
                     did. */
                  if (yychar != CYPHER_CYPHER_YYerror)
                    yyreportSyntaxError (&yystack, context);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue, context));
            }
        }

      /* Nondeterministic mode. */
      while (yytrue)
        {
          yysymbol_kind_t yytoken_to_shift;
          YYPTRDIFF_T yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != CYPHER_CYPHER_YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn, &yylloc, context));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, &yylloc, context, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack, context));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yystack.yyerror_range[1].yystate.yyloc = yylloc;
              yyreportSyntaxError (&yystack, context);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to CYPHER_CYPHER_YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = CYPHER_CYPHER_YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              yy_state_t yystate = yystack.yytops.yystates[yys]->yylrState;
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken_to_shift,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YY_DPRINTF ((stderr, "On stack %ld, ", YY_CAST (long, yys)));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval, &yylloc);
              YY_DPRINTF ((stderr, "Stack %ld now in state %d\n",
                           YY_CAST (long, yys),
                           yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack, context));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, context);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;

 yybuglab:
  YY_ASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturnlab;

 yyexhaustedlab:
  yyerror (&yylloc, context, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;

 yyreturnlab:
  if (yychar != CYPHER_CYPHER_YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, &yylloc, context);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          YYPTRDIFF_T yysize = yystack.yytops.yysize;
          YYPTRDIFF_T yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                    yystack.yyerror_range[1].yystate.yyloc = yys->yyloc;
                    if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys, context);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if CYPHER_YYDEBUG
/* Print *YYS and its predecessors. */
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YY_FPRINTF ((stderr, " -> "));
    }
  YY_FPRINTF ((stderr, "%d@%ld", yys->yylrState, YY_CAST (long, yys->yyposn)));
}

/* Print YYS (possibly NULL) and its predecessors. */
static void
yypstates (yyGLRState* yys)
{
  if (yys == YY_NULLPTR)
    YY_FPRINTF ((stderr, "<null>"));
  else
    yy_yypstack (yys);
  YY_FPRINTF ((stderr, "\n"));
}

/* Print the stack #YYK.  */
static void
yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

/* Print all the stacks.  */
static void
yypdumpstack (yyGLRStack* yystackp)
{
#define YYINDEX(YYX)                                                    \
  YY_CAST (long,                                                        \
           ((YYX)                                                       \
            ? YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX)) - yystackp->yyitems \
            : -1))

  yyGLRStackItem* yyp;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YY_FPRINTF ((stderr, "%3ld. ",
                   YY_CAST (long, yyp - yystackp->yyitems)));
      if (*YY_REINTERPRET_CAST (yybool *, yyp))
        {
          YY_ASSERT (yyp->yystate.yyisState);
          YY_ASSERT (yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Res: %d, LR State: %d, posn: %ld, pred: %ld",
                       yyp->yystate.yyresolved, yyp->yystate.yylrState,
                       YY_CAST (long, yyp->yystate.yyposn),
                       YYINDEX (yyp->yystate.yypred)));
          if (! yyp->yystate.yyresolved)
            YY_FPRINTF ((stderr, ", firstVal: %ld",
                         YYINDEX (yyp->yystate.yysemantics.yyfirstVal)));
        }
      else
        {
          YY_ASSERT (!yyp->yystate.yyisState);
          YY_ASSERT (!yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Option. rule: %d, state: %ld, next: %ld",
                       yyp->yyoption.yyrule - 1,
                       YYINDEX (yyp->yyoption.yystate),
                       YYINDEX (yyp->yyoption.yynext)));
        }
      YY_FPRINTF ((stderr, "\n"));
    }

  YY_FPRINTF ((stderr, "Tops:"));
  {
    YYPTRDIFF_T yyi;
    for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
      YY_FPRINTF ((stderr, "%ld: %ld; ", YY_CAST (long, yyi),
                   YYINDEX (yystackp->yytops.yystates[yyi])));
    YY_FPRINTF ((stderr, "\n"));
  }
#undef YYINDEX
}
#endif

#undef yylval
#undef yychar
#undef yynerrs
#undef yylloc

/* Substitute the variable and function names.  */
#define yyparse cypher_yyparse
#define yylex   cypher_yylex
#define yyerror cypher_yyerror
#define yylval  cypher_yylval
#define yychar  cypher_yychar
#define yydebug cypher_yydebug
#define yynerrs cypher_yynerrs
#define yylloc  cypher_yylloc


#line 1601 "src/backend/parser/cypher_gram.y"


/* Error handling function */
void cypher_yyerror(CYPHER_YYLTYPE *yylloc, cypher_parser_context *context, const char *msg)
{
    if (!context || !msg) {
        return;
    }

    context->has_error = true;
    context->error_location = yylloc ? yylloc->first_line : -1;
    context->error_column = yylloc ? yylloc->first_column : -1;

    /* Create error message with line number - Bison's detailed error mode
     * provides good context about what was expected */
    char error_buffer[512];
    if (yylloc && yylloc->first_line > 0) {
        if (yylloc->first_column > 0) {
            snprintf(error_buffer, sizeof(error_buffer),
                     "Line %d, Col %d: %s", yylloc->first_line, yylloc->first_column, msg);
        } else {
            snprintf(error_buffer, sizeof(error_buffer),
                     "Line %d: %s", yylloc->first_line, msg);
        }
    } else {
        snprintf(error_buffer, sizeof(error_buffer), "%s", msg);
    }

    free(context->error_message);
    context->error_message = strdup(error_buffer);
}

/* cypher_yylex function is implemented in cypher_parser.c */
