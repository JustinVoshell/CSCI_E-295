#include <string.h>

#include "code_table.h"
#include "tokens.h"
#include "token_attributes.h"

/* code_table.c
   Justin Voshell - justin.voshell@me.com
   CSCI-E295 Spring 2012

   Provides a facility for mapping codes returned by the scanner into
   string names that are more appropriate for display to a user.  

   The approach here mimics the one taken in Willenson's scanner_tokens.c: an 
   array is used to map a constant's value to a stringification of the 
   constant.

   I've added a macro to allow for a string message to be used instead of the
   stringification.  This is used for error messages.
*/

/* 
   Store stringification of constant name at constant's value in 
   _encoding array
*/
#define ENCODE(CODE) encoding_[CODE] = #CODE

/* Store message at constant's value in _encoding array */
#define ENCODE_MESSAGE(CODE, MESSAGE) encoding_[CODE] = MESSAGE

/* Mapping of code values to string descriptions */
char* encoding_[CODE_TABLE_SIZE] = { NULL };

/* decode
  
   Returns a string value associated with the provided code.
   NOTE: init_code_table() must be called once before calling this function.

   Parameters   : code (const int)
                  - code value to fetch string for.  Should be a code
                    defined in scanner_codes.h

   Returns      : string value saved in table for code.
                  NULL if no string value found.

   Side-effects : none
*/
const char* decode(const int code)
{
  if (IS(CODE, code)) {
    return encoding_[code];
  }
  
  return NULL;
}

/* init_code_table

   Must be called once to load strings into code table.

   Parameters   : none

   Returns      : none

   Side-effects : Modifies values in _encoding to point to string constants.
*/
void init_code_table()
{  
  ENCODE(IDENTIFIER);
  ENCODE(LITERAL_STRING);
  ENCODE(LITERAL_NUMBER);
	ENCODE(LITERAL_CHAR);
	ENCODE(LITERAL_SHORT);
	ENCODE(LITERAL_INT);
	ENCODE(LITERAL_ULONG);
	ENCODE(NO_OVERFLOW);
	ENCODE(HAS_OVERFLOW);
  ENCODE(BREAK);
  ENCODE(CHAR);
  ENCODE(CONTINUE);
  ENCODE(DO);
  ENCODE(ELSE);
  ENCODE(FOR);
  ENCODE(GOTO);
  ENCODE(IF);
  ENCODE(INT);
  ENCODE(LONG);
  ENCODE(RETURN);
  ENCODE(SHORT);
  ENCODE(SIGNED);
  ENCODE(UNSIGNED);
  ENCODE(VOID);
  ENCODE(WHILE);
  ENCODE(ASTERISK);
  ENCODE(COLON);
  ENCODE(DASH);
  ENCODE(PLUS);
  ENCODE(QUESTION_MARK);
  ENCODE(ASSIGN);
  ENCODE(ASSIGN_BITWISE_AND);
  ENCODE(ASSIGN_BITWISE_OR);
  ENCODE(ASSIGN_BITWISE_XOR);
  ENCODE(ASSIGN_LEFT_SHIFT);
  ENCODE(ASSIGN_RIGHT_SHIFT);
  ENCODE(ASSIGN_SUM);
  ENCODE(ASSIGN_DIFFERENCE);
  ENCODE(ASSIGN_PRODUCT);
  ENCODE(ASSIGN_QUOTIENT);
  ENCODE(ASSIGN_REMAINDER);
  ENCODE(BITWISE_AND);
  ENCODE(BITWISE_OR);
  ENCODE(BITWISE_XOR);
  ENCODE(BITWISE_NEGATION);
  ENCODE(LEFT_SHIFT);
  ENCODE(RIGHT_SHIFT);
  ENCODE(DIVISION);
  ENCODE(REMAINDER);
  ENCODE(INCREMENT);
  ENCODE(DECREMENT);
  ENCODE(LESS);
  ENCODE(LESS_OR_EQUAL);
  ENCODE(GREATER);
  ENCODE(GREATER_OR_EQUAL);
  ENCODE(EQUAL_TO);
  ENCODE(NOT_EQUAL);
  ENCODE(LOGICAL_AND);
  ENCODE(LOGICAL_OR);
  ENCODE(LOGICAL_NEGATION);
  ENCODE(LEFT_PAREN);
  ENCODE(RIGHT_PAREN);
  ENCODE(LEFT_BRACKET);
  ENCODE(RIGHT_BRACKET);
  ENCODE(LEFT_BRACE);
  ENCODE(RIGHT_BRACE);
  ENCODE(STATEMENT_TERMINATOR);
  ENCODE(SEQUENTIAL_EVAL);

  ENCODE_MESSAGE(E_NO_MATCHING_TOKEN, "No matching token");
  ENCODE_MESSAGE(E_BAD_LITERAL_CHAR, "Invalid character literal");
  ENCODE_MESSAGE(E_BAD_OCTAL_LITERAL, "Invalid octal code in character literal");
  ENCODE_MESSAGE(E_UNTERM_CHAR, "Unterminated character literal");
  ENCODE_MESSAGE(E_EOF_COMMENT, "EOF reached. Unterminated comment");
  ENCODE_MESSAGE(E_EOF_CHAR, "EOF reached. Unterminated character literal");
  ENCODE_MESSAGE(E_EOF_STR, "EOF reached. Unterminated string");
  ENCODE_MESSAGE(E_UNTERM_STR, "Unterminated string");
  ENCODE_MESSAGE(E_BAD_CHAR_ESCAPE, "Invalid character escape sequence.");
  ENCODE_MESSAGE(E_OUT_OF_MEMORY, "Out of memory!");

}
