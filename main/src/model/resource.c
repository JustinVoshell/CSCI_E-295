#include <string.h>

#include "model/resource.h"
#include "model/node.h"
#include "model/tokens.h"

#define RECORD(CODE) strings_[CODE] = #CODE
#define RECORD_MESSAGE(CODE, MESSAGE) strings_[CODE] = MESSAGE

char* strings_[RESOURCE_TABLE_SIZE] = { 0 };

const char* resource(const int code)
{
	if (code < 0 || code > RESOURCE_TABLE_SIZE) { return 0; }
  return strings_[code]; 
}

void resource_init()
{  
  RECORD(IDENTIFIER);
  RECORD(LITERAL_STRING);
  RECORD(LITERAL_NUMBER);
	RECORD(INTEGER_DATA_VOID);
	RECORD(INTEGER_DATA_SIGNED_CHAR);
	RECORD(INTEGER_DATA_UNSIGNED_CHAR);
	RECORD(INTEGER_DATA_SIGNED_SHORT);
	RECORD(INTEGER_DATA_UNSIGNED_SHORT);
	RECORD(INTEGER_DATA_SIGNED_INT);
	RECORD(INTEGER_DATA_UNSIGNED_INT);
	RECORD(INTEGER_DATA_SIGNED_LONG);
	RECORD(INTEGER_DATA_UNSIGNED_LONG);
	RECORD(INTEGER_DATA_NO_OVERFLOW);
	RECORD(INTEGER_DATA_OVERFLOW);
  RECORD(BREAK);
  RECORD(CHAR);
  RECORD(CONTINUE);
  RECORD(DO);
  RECORD(ELSE);
  RECORD(FOR);
  RECORD(GOTO);
  RECORD(IF);
  RECORD(INT);
  RECORD(LONG);
  RECORD(RETURN);
  RECORD(SHORT);
  RECORD(SIGNED);
  RECORD(UNSIGNED);
  RECORD(VOID);
  RECORD(WHILE);
  RECORD(ASTERISK);
  RECORD(COLON);
  RECORD(DASH);
  RECORD(PLUS);
  RECORD(QUESTION_MARK);
  RECORD(ASSIGN);
  RECORD(ASSIGN_BITWISE_AND);
  RECORD(ASSIGN_BITWISE_OR);
  RECORD(ASSIGN_BITWISE_XOR);
  RECORD(ASSIGN_LEFT_SHIFT);
  RECORD(ASSIGN_RIGHT_SHIFT);
  RECORD(ASSIGN_SUM);
  RECORD(ASSIGN_DIFFERENCE);
  RECORD(ASSIGN_PRODUCT);
  RECORD(ASSIGN_QUOTIENT);
  RECORD(ASSIGN_REMAINDER);
  RECORD(BITWISE_AND);
  RECORD(BITWISE_OR);
  RECORD(BITWISE_XOR);
  RECORD(BITWISE_NEGATION);
  RECORD(LEFT_SHIFT);
  RECORD(RIGHT_SHIFT);
  RECORD(DIVISION);
  RECORD(REMAINDER);
  RECORD(INCREMENT);
  RECORD(DECREMENT);
  RECORD(LESS);
  RECORD(LESS_OR_EQUAL);
  RECORD(GREATER);
  RECORD(GREATER_OR_EQUAL);
  RECORD(EQUAL_TO);
  RECORD(NOT_EQUAL);
  RECORD(LOGICAL_AND);
  RECORD(LOGICAL_OR);
  RECORD(LOGICAL_NEGATION);
  RECORD(LEFT_PAREN);
  RECORD(RIGHT_PAREN);
  RECORD(LEFT_BRACKET);
  RECORD(RIGHT_BRACKET);
  RECORD(LEFT_BRACE);
  RECORD(RIGHT_BRACE);
  RECORD(SEMICOLON);
  RECORD(SEQUENTIAL_EVAL);
  
  RECORD_MESSAGE(ERROR_NO_MATCHING_TOKEN, "No matching token");
  RECORD_MESSAGE(ERROR_BAD_LITERAL_CHAR , "Invalid character literal");
  RECORD_MESSAGE(ERROR_BAD_OCTAL_ESCAPE , "Invalid octal escape sequence");
  RECORD_MESSAGE(ERROR_UNTERM_CHAR      , "Unterminated character literal");
  RECORD_MESSAGE(ERROR_EOF_COMMENT      , "EOF reached. Unterminated comment");
  RECORD_MESSAGE(ERROR_EOF_CHAR         , "EOF reached. Unterminated character literal");
  RECORD_MESSAGE(ERROR_EOF_STR          , "EOF reached. Unterminated string");
  RECORD_MESSAGE(ERROR_UNTERM_STR       , "Unterminated string");
  RECORD_MESSAGE(ERROR_BAD_CHAR_ESCAPE  , "Invalid character escape sequence.");
  RECORD_MESSAGE(ERROR_OUT_OF_MEMORY    , "Out of memory!");
}
