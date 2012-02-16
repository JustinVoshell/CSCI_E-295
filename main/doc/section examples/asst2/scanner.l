%option yylineno
%option nounput
%option noyywrap

%{
  /*
   * scanner.l
   *
   * This file contains the specification for the (f)lex generated scanner
   * for the CSCI-E295 source language. It also contains some helper routines
   * which create structures to be returned to the calling program. 
   *
   */
   
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <assert.h>

    #include "node.h"
    #define YYSTYPE node *
    
    #ifdef __SCANNER
      #include "scanner_tokens.h"
      extern YYSTYPE yylval;
    #endif
    
    #ifdef __PARSER
      #include "parse.h"
    #endif
    
    node *create_identifier(char *text, int length);
    
    node *create_number(char *text, int length);
%}

newline         \n
ws              [ \t\v\f]

digit           [[:digit:]]
letter          [[:alpha:]]
nondigit        {letter}|_

id              {nondigit}({nondigit}|{digit})*

number          {digit}+

%%

{newline}   /* do nothing; lex is counting lines */
{ws}        /* do nothing */

  /* operators begin */
\+          return PLUS; 
-           return MINUS; 
\=          return EQUALS; 

\(          return LEFT_PAREN; 
\)          return RIGHT_PAREN; 

;           return SEMICOLON; 
  /* operators end */

  /* constants begin */
{number}    yylval = (YYSTYPE)create_number(yytext, yyleng); return NUMBER;
  /* constants end */

  /* identifiers */
{id}        yylval = (YYSTYPE)create_identifier(yytext, yyleng); return IDENTIFIER;

.           return -1;

%%

 /*
  * create_identifier - copy yytext and create an identifier from it
  *
  * Parameters:
  *   text - string - contains the name of the identifier as matched in the source program
  *   length - integer - the length of text (not including terminating NUL)
  *
  * Returns:
  *   an identifier node with a NUL-terminated string in newly allocated memory, containing 
  *   the text copied from the source program.
  *
  * Side-effects:
  *   memory may be allocated on the heap.
  *
  */
node *create_identifier(char *text, int length) {
  char *id;

  id = (char *)malloc(sizeof(char) * (length + 1));
  assert(NULL != id);
  strcpy(id, text);
  return create_identifier_node(id);
}

 /*
  * create_number - read the value of a number from a string
  *
  * Parameters:
  *   text - string - contains the constant as matched in the source program
  *   length - integer - the length of text (not including terminating NUL)
  *
  * Returns:
  *   a number node containing the value from text and an overflow indication
  *
  */
node *create_number(char *text, int length) {
  assert(length > 0);
  return create_number_node(strtoul(text, NULL, 10), 0);
}