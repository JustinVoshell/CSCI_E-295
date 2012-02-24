#ifndef JHV9902116_201202211650
#define JHV9902116_201202211650

/*
	Tokens.h
	
	Defines constants representing token values for use with the scanner.  When
	the scanner is run in conjunction with bison, bison generates its own header
	file with these constants defined.
*/

#include "code_table.h"

#define IDENTIFIER           ADD_CODE(HAS_ATTRIBUTE, 1)    
#define LITERAL_STRING       ADD_CODE(HAS_ATTRIBUTE, 2)    
#define LITERAL_NUMBER       ADD_CODE(HAS_ATTRIBUTE, 3)
   
#define BREAK                ADD_CODE(KEYWORD, 1)    
#define CHAR                 ADD_CODE(KEYWORD, 2)  
#define CONTINUE             ADD_CODE(KEYWORD, 3) 
#define DO                   ADD_CODE(KEYWORD, 4)
#define ELSE                 ADD_CODE(KEYWORD, 5)
#define FOR                  ADD_CODE(KEYWORD, 6)
#define GOTO                 ADD_CODE(KEYWORD, 7)
#define IF                   ADD_CODE(KEYWORD, 8)
#define INT                  ADD_CODE(KEYWORD, 9)
#define LONG                 ADD_CODE(KEYWORD, 10) 
#define RETURN               ADD_CODE(KEYWORD, 11)
#define SHORT                ADD_CODE(KEYWORD, 12)
#define SIGNED               ADD_CODE(KEYWORD, 13)
#define UNSIGNED             ADD_CODE(KEYWORD, 14)
#define VOID                 ADD_CODE(KEYWORD, 15)
#define WHILE                ADD_CODE(KEYWORD, 16)

#define ASTERISK             ADD_CODE(OPERATOR, 1)  
#define COLON                ADD_CODE(OPERATOR, 2)  
#define DASH                 ADD_CODE(OPERATOR, 3)
#define PLUS                 ADD_CODE(OPERATOR, 4)
#define QUESTION_MARK        ADD_CODE(OPERATOR, 5)
#define ASSIGN               ADD_CODE(OPERATOR, 6)
#define ASSIGN_BITWISE_AND   ADD_CODE(OPERATOR, 7)
#define ASSIGN_BITWISE_OR    ADD_CODE(OPERATOR, 8)
#define ASSIGN_BITWISE_XOR   ADD_CODE(OPERATOR, 9)
#define ASSIGN_LEFT_SHIFT    ADD_CODE(OPERATOR, 10) 
#define ASSIGN_RIGHT_SHIFT   ADD_CODE(OPERATOR, 11)
#define ASSIGN_SUM           ADD_CODE(OPERATOR, 12)
#define ASSIGN_DIFFERENCE    ADD_CODE(OPERATOR, 13)
#define ASSIGN_PRODUCT       ADD_CODE(OPERATOR, 14)
#define ASSIGN_QUOTIENT      ADD_CODE(OPERATOR, 15)
#define ASSIGN_REMAINDER     ADD_CODE(OPERATOR, 16)
#define BITWISE_AND          ADD_CODE(OPERATOR, 17)
#define BITWISE_OR           ADD_CODE(OPERATOR, 18)
#define BITWISE_XOR          ADD_CODE(OPERATOR, 19)
#define BITWISE_NEGATION     ADD_CODE(OPERATOR, 20)
#define LEFT_SHIFT           ADD_CODE(OPERATOR, 21)
#define RIGHT_SHIFT          ADD_CODE(OPERATOR, 22)
#define DIVISION             ADD_CODE(OPERATOR, 23)
#define REMAINDER            ADD_CODE(OPERATOR, 24)
#define INCREMENT            ADD_CODE(OPERATOR, 25)
#define DECREMENT            ADD_CODE(OPERATOR, 26)
#define LESS                 ADD_CODE(OPERATOR, 27)
#define LESS_OR_EQUAL        ADD_CODE(OPERATOR, 28)
#define GREATER              ADD_CODE(OPERATOR, 29)
#define GREATER_OR_EQUAL     ADD_CODE(OPERATOR, 30)
#define EQUAL_TO             ADD_CODE(OPERATOR, 31)
#define NOT_EQUAL            ADD_CODE(OPERATOR, 32)
#define LOGICAL_AND          ADD_CODE(OPERATOR, 33)
#define LOGICAL_OR           ADD_CODE(OPERATOR, 34)
#define LOGICAL_NEGATION     ADD_CODE(OPERATOR, 35)

#define LEFT_PAREN           ADD_CODE(SEPARATOR, 1)
#define RIGHT_PAREN          ADD_CODE(SEPARATOR, 2)  
#define LEFT_BRACKET         ADD_CODE(SEPARATOR, 3)
#define RIGHT_BRACKET        ADD_CODE(SEPARATOR, 4)
#define LEFT_BRACE           ADD_CODE(SEPARATOR, 5)
#define RIGHT_BRACE          ADD_CODE(SEPARATOR, 6)
#define STATEMENT_TERMINATOR ADD_CODE(SEPARATOR, 7)
#define SEQUENTIAL_EVAL      ADD_CODE(SEPARATOR, 8)

#endif /*JHV9902116_201202211650*/