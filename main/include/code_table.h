#ifndef JHV9902116_201202090917
#define JHV9902116_201202090917

/* code_table.h
   Justin Voshell - justin.voshell@me.com
   CSCI E-295 Spring 2012
  
   Provides prototypes for the decoding facility implemented in 
   code_table.c.  

	 Defines error codes & code ranges. 
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
  Code ranges
*/
#define CODE_TABLE_SIZE	2999
#define RANGE(name, first, max)\
	static int code_table_first_##name = first;\
	static int code_table_max_##name = max;

#define IS(name, value) (value <= code_table_first_##name && value >= code_table_max_##name)
#define ADD_CODE(name, value) (code_table_first_##name + value)

RANGE(CODE, 1000, CODE_TABLE_SIZE)
RANGE(TOKEN, 1000, 1999)
RANGE(HAS_ATTRIBUTE, 1000, 1009)
RANGE(KEYWORD, 1010, 1029)
RANGE(OPERATOR, 1030, 1079)
RANGE(SEPARATOR, 1080, 1090)
RANGE(ERROR, 2000, CODE_TABLE_SIZE)
RANGE(EOF_ERROR, 2100, 2119)

/* 
	Error codes
*/

#define E_NO_MATCHING_TOKEN    ADD_CODE(ERROR, 1)
#define E_BAD_LITERAL_CHAR     ADD_CODE(ERROR, 2)
#define E_UNTERM_CHAR          ADD_CODE(ERROR, 3)
#define E_OUT_OF_MEMORY        ADD_CODE(ERROR, 7)
#define E_UNTERM_STR           ADD_CODE(ERROR, 8)
#define E_BAD_CHAR_ESCAPE      ADD_CODE(ERROR, 9)
#define E_BAD_OCTAL_LITERAL    ADD_CODE(ERROR, 10)
#define E_EOF_COMMENT          ADD_CODE(EOF_ERROR, 1)
#define E_EOF_CHAR             ADD_CODE(EOF_ERROR, 2)
#define E_EOF_STR              ADD_CODE(EOF_ERROR, 3)
  
#endif /*JHV9902116_201202090917*/