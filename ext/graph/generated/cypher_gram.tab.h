/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Skeleton interface for Bison GLR parsers in C

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

#ifndef YY_CYPHER_YY_SRC_GENERATED_CYPHER_GRAM_TAB_H_INCLUDED
# define YY_CYPHER_YY_SRC_GENERATED_CYPHER_GRAM_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef CYPHER_YYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define CYPHER_YYDEBUG 1
#  else
#   define CYPHER_YYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define CYPHER_YYDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined CYPHER_YYDEBUG */
#if CYPHER_YYDEBUG
extern int cypher_yydebug;
#endif
/* "%code requires" blocks.  */
#line 20 "src/backend/parser/cypher_gram.y"

#include <stdint.h>
#include <stdbool.h>

#line 57 "src/generated/cypher_gram.tab.h"

/* Token kinds.  */
#ifndef CYPHER_YYTOKENTYPE
# define CYPHER_YYTOKENTYPE
  enum cypher_yytokentype
  {
    CYPHER_CYPHER_YYEMPTY = -2,
    CYPHER_YYEOF = 0,              /* "end of file"  */
    CYPHER_CYPHER_YYerror = 256,   /* error  */
    CYPHER_CYPHER_YYUNDEF = 257,   /* "invalid token"  */
    CYPHER_INTEGER = 258,          /* INTEGER  */
    CYPHER_DECIMAL = 259,          /* DECIMAL  */
    CYPHER_STRING = 260,           /* STRING  */
    CYPHER_IDENTIFIER = 261,       /* IDENTIFIER  */
    CYPHER_PARAMETER = 262,        /* PARAMETER  */
    CYPHER_BQIDENT = 263,          /* BQIDENT  */
    CYPHER_NOT_EQ = 264,           /* NOT_EQ  */
    CYPHER_LT_EQ = 265,            /* LT_EQ  */
    CYPHER_GT_EQ = 266,            /* GT_EQ  */
    CYPHER_DOT_DOT = 267,          /* DOT_DOT  */
    CYPHER_TYPECAST = 268,         /* TYPECAST  */
    CYPHER_PLUS_EQ = 269,          /* PLUS_EQ  */
    CYPHER_REGEX_MATCH = 270,      /* REGEX_MATCH  */
    CYPHER_MATCH = 271,            /* MATCH  */
    CYPHER_RETURN = 272,           /* RETURN  */
    CYPHER_CREATE = 273,           /* CREATE  */
    CYPHER_WHERE = 274,            /* WHERE  */
    CYPHER_WITH = 275,             /* WITH  */
    CYPHER_SET = 276,              /* SET  */
    CYPHER_DELETE = 277,           /* DELETE  */
    CYPHER_REMOVE = 278,           /* REMOVE  */
    CYPHER_MERGE = 279,            /* MERGE  */
    CYPHER_UNWIND = 280,           /* UNWIND  */
    CYPHER_DETACH = 281,           /* DETACH  */
    CYPHER_FOREACH = 282,          /* FOREACH  */
    CYPHER_CALL = 283,             /* CALL  */
    CYPHER_OPTIONAL = 284,         /* OPTIONAL  */
    CYPHER_DISTINCT = 285,         /* DISTINCT  */
    CYPHER_ORDER = 286,            /* ORDER  */
    CYPHER_BY = 287,               /* BY  */
    CYPHER_SKIP = 288,             /* SKIP  */
    CYPHER_LIMIT = 289,            /* LIMIT  */
    CYPHER_AS = 290,               /* AS  */
    CYPHER_ASC = 291,              /* ASC  */
    CYPHER_DESC = 292,             /* DESC  */
    CYPHER_AND = 293,              /* AND  */
    CYPHER_OR = 294,               /* OR  */
    CYPHER_XOR = 295,              /* XOR  */
    CYPHER_NOT = 296,              /* NOT  */
    CYPHER_IN = 297,               /* IN  */
    CYPHER_IS = 298,               /* IS  */
    CYPHER_NULL_P = 299,           /* NULL_P  */
    CYPHER_TRUE_P = 300,           /* TRUE_P  */
    CYPHER_FALSE_P = 301,          /* FALSE_P  */
    CYPHER_EXISTS = 302,           /* EXISTS  */
    CYPHER_ANY = 303,              /* ANY  */
    CYPHER_NONE = 304,             /* NONE  */
    CYPHER_SINGLE = 305,           /* SINGLE  */
    CYPHER_REDUCE = 306,           /* REDUCE  */
    CYPHER_UNION = 307,            /* UNION  */
    CYPHER_ALL = 308,              /* ALL  */
    CYPHER_CASE = 309,             /* CASE  */
    CYPHER_WHEN = 310,             /* WHEN  */
    CYPHER_THEN = 311,             /* THEN  */
    CYPHER_ELSE = 312,             /* ELSE  */
    CYPHER_END_P = 313,            /* END_P  */
    CYPHER_ON = 314,               /* ON  */
    CYPHER_SHORTESTPATH = 315,     /* SHORTESTPATH  */
    CYPHER_ALLSHORTESTPATHS = 316, /* ALLSHORTESTPATHS  */
    CYPHER_PATTERN = 317,          /* PATTERN  */
    CYPHER_EXPLAIN = 318,          /* EXPLAIN  */
    CYPHER_LOAD = 319,             /* LOAD  */
    CYPHER_CSV = 320,              /* CSV  */
    CYPHER_FROM = 321,             /* FROM  */
    CYPHER_HEADERS = 322,          /* HEADERS  */
    CYPHER_FIELDTERMINATOR = 323,  /* FIELDTERMINATOR  */
    CYPHER_STARTS = 324,           /* STARTS  */
    CYPHER_ENDS = 325,             /* ENDS  */
    CYPHER_CONTAINS = 326,         /* CONTAINS  */
    CYPHER_UNARY_MINUS = 327,      /* UNARY_MINUS  */
    CYPHER_UNARY_PLUS = 328        /* UNARY_PLUS  */
  };
  typedef enum cypher_yytokentype cypher_yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined CYPHER_YYSTYPE && ! defined CYPHER_YYSTYPE_IS_DECLARED
union CYPHER_YYSTYPE
{
#line 44 "src/backend/parser/cypher_gram.y"

    int64_t integer;
    double decimal;
    char *string;
    bool boolean;
    
    /* AST node types */
    ast_node *node;
    ast_list *list;
    
    /* Specific node types for type safety */
    cypher_query *query;
    cypher_match *match;
    cypher_return *return_clause;
    cypher_create *create;
    cypher_merge *merge;
    cypher_set *set;
    cypher_set_item *set_item;
    cypher_delete *delete;
    cypher_delete_item *delete_item;
    cypher_remove *remove;
    cypher_remove_item *remove_item;
    cypher_with *with_clause;
    cypher_union *union_query;
    cypher_return_item *return_item;
    cypher_order_by_item *order_by_item;
    cypher_literal *literal;
    cypher_identifier *identifier;
    cypher_parameter *parameter;
    cypher_label_expr *label_expr;
    cypher_not_expr *not_expr;
    cypher_binary_op *binary_op;
    cypher_exists_expr *exists_expr;
    cypher_node_pattern *node_pattern;
    cypher_rel_pattern *rel_pattern;
    cypher_varlen_range *varlen_range;
    cypher_path *path;
    cypher_map *map;
    cypher_map_pair *map_pair;
    cypher_list_comprehension *list_comprehension;

#line 189 "src/generated/cypher_gram.tab.h"

};
typedef union CYPHER_YYSTYPE CYPHER_YYSTYPE;
# define CYPHER_YYSTYPE_IS_TRIVIAL 1
# define CYPHER_YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined CYPHER_YYLTYPE && ! defined CYPHER_YYLTYPE_IS_DECLARED
typedef struct CYPHER_YYLTYPE CYPHER_YYLTYPE;
struct CYPHER_YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define CYPHER_YYLTYPE_IS_DECLARED 1
# define CYPHER_YYLTYPE_IS_TRIVIAL 1
#endif



int cypher_yyparse (cypher_parser_context *context);

#endif /* !YY_CYPHER_YY_SRC_GENERATED_CYPHER_GRAM_TAB_H_INCLUDED  */
