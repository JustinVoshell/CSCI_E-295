#ifndef JHV9902116_201202090917
#define JHV9902116_201202090917

#include <stddef.h>

/* scanner_codes.h
   Justin Voshell - justin.voshell@me.com
   CSCI E-295 Spring 2012
  
   Single header used across files in scanner.

   Defines codes for returning token values and error messages from flex.
   Provides prototypes for the decoding facility implemented in 
   scanner_codes.c. 
*/

/* init_code_table()

   Initializes collection of strings used by decode.  Must be called once 
   before calling using decode().

   Parameters   : void
   Returns      : void

   Side-effects : String constants are added to the code table.
*/
void init_code_table(void);

/* decode()

   Retrieve string for code.

   Parameters   : code (int)
                  - An integer value defined in this file

   Returns      : Pointer to string value for code.
                  NULL if no string is found for code.

   Side-effects : None
*/
const char* decode(const int code);

/*
   Codes

   Code ranges are enclosed with FIRST_RANGE / LAST_RANGE constants.
   These are used by the IS(RANGE, VALUE) macro to determine if a code is part
   of a particular range.

   For example, IS(KEYWORD, SHORT) would expand to the Boolean expression
   (SHORT >= FIRST_KEYWORD && SHORT >= LAST_KEYWORD)
*/

#define IS(RANGE, VALUE) (VALUE >= FIRST_##RANGE && VALUE <= LAST_##RANGE)

#define FIRST_CODE               0
#define FIRST_TOKEN              0
/*
   Tokens that carry attribute values
*/
#define FIRST_WITH_ATTRIBUTE     1
#define IDENTIFIER               1
#define LITERAL_STRING           2
#define LITERAL_INTEGER          3
#define LAST_WITH_ATTRIBUTE      3

/*
   Keywords
*/
#define FIRST_KEYWORD          101
#define BREAK                  101
#define CHAR                   102
#define CONTINUE               103
#define DO                     104
#define ELSE                   105
#define FOR                    106
#define GOTO                   107
#define IF                     108
#define INT                    109
#define LONG                   110
#define RETURN                 111
#define SHORT                  112
#define SIGNED                 113
#define UNSIGNED               114
#define VOID                   115
#define WHILE                  116
#define LAST_KEYWORD           116 

/*
  Operators
*/
#define FIRST_OPERATOR         119
#define ASTERISK               119
#define COLON                  120
#define DASH                   121
#define PLUS                   122
#define QUESTION_MARK          123
#define ASSIGN                 124
#define ASSIGN_BITWISE_AND     125
#define ASSIGN_BITWISE_OR      126
#define ASSIGN_BITWISE_XOR     127
#define ASSIGN_LEFT_SHIFT      128
#define ASSIGN_RIGHT_SHIFT     129
#define ASSIGN_SUM             130
#define ASSIGN_DIFFERENCE      131
#define ASSIGN_PRODUCT         132
#define ASSIGN_QUOTIENT        133
#define ASSIGN_REMAINDER       134
#define BITWISE_AND            135
#define BITWISE_OR             136
#define BITWISE_XOR            137
#define BITWISE_NEGATION       138
#define LEFT_SHIFT             139
#define RIGHT_SHIFT            140
#define DIVISION               141
#define REMAINDER              142
#define INCREMENT              143
#define DECREMENT              144
#define LESS                   145
#define LESS_OR_EQUAL          146
#define GREATER                147
#define GREATER_OR_EQUAL       148
#define EQUAL_TO               149
#define NOT_EQUAL              150
#define LOGICAL_AND            151
#define LOGICAL_OR             152
#define LOGICAL_NEGATION       153
#define LAST_OPERATOR          153

/*
  Separators
*/
#define FIRST_SEPARATOR        154
#define LEFT_PAREN             154
#define RIGHT_PAREN            155
#define LEFT_BRACKET           156
#define RIGHT_BRACKET          157
#define LEFT_BRACE             158
#define RIGHT_BRACE            159
#define STATEMENT_TERMINATOR   160
#define SEQUENTIAL_EVAL        161
#define LAST_SEPARATOR         161

#define LAST_TOKEN             161

/*
  Errors
*/
#define FIRST_ERROR            201
#define E_NO_MATCHING_TOKEN    201
#define E_BAD_LITERAL_CHAR     202
#define E_UNTERM_CHAR          203
#define FIRST_EOF_ERROR        204
#define E_EOF_COMMENT          204
#define E_EOF_CHAR             205
#define E_EOF_STR              206
#define LAST_EOF_ERROR         206
#define E_OUT_OF_MEMORY        207
#define E_UNTERM_STR           208
#define E_BAD_CHAR_ESCAPE      209
#define E_BAD_OCTAL_LITERAL    210
#define LAST_ERROR             210

#define LAST_CODE              210

#endif
