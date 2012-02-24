%{
  /* 
   scanner.l
   Justin Voshell - justin.voshell@me.com
   CSCI E-295 Spring 2012

   Scanner definition to be consumed by flex in standalone scanning
   mode or in conjunction with bison.  

   Example code provided by Daniel Willenson and Dr. James Frankel was
   consulted in the development of this file as well as the flex manual.

   Source language is specified in Problem Set 1 and Harbison & Steele.  

   This file is heavily commented to explain the approach taken to scanning
   the different lexical elements of the source language.
  */

  #include <stdio.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <limits.h>

  #include "tokens.h"
  #include "token_attributes.h"

  /* We use yyval to pass token attriute values to the client */  
  #define YYSTYPE void*
  extern YYSTYPE yylval;

  /* 
     String buffer
     
     These functions initialize and manipulate the string buffer used to build
     up representations of string literals.  For now, string literals longer 
     than 64KB are not allowed.  In the future I may add a facility for growing
     the string buffer to store longer literals.
  */
  #define MAX_STR_LEN LITERAL_SHORT_MAX
  char* string_buffer;
  char* string_buffer_cursor;
  int initialize_string_buffer();
  int remaining_buffer_capacity();
  int add_char_to_string_buffer(const char charValue);
  int add_octal_to_string_buffer(const char* octalLiteral);
  int add_string_to_string_buffer(const char* string, const int length);

  /*
    Attribute constructors

    These functions construct the various values passed to the client as 
    yylval attributes.  The memory allocated in these methods is the 
    responsibility of the client.
  */ 
  char* make_id(const char* text, const int length);
  integer* make_integer(const char* text);
  integer* make_integer_from_char(const int charValue);
  integer* make_integer_from_octal(const char* text);
  string* make_string();

%}

%option yylineno                        
%option nounput                         
%option yywrap                          

 /* 
   Start conditions are used to help handle quoted elements 
 */
%x COMMENT
%x CHARACTER
%x STRING

 /*
   Some definitions:
 
   Whitespace is a sequence of any space, tab, vertical tab, form feed or new 
   line character.

   Identifiers are a sequence of letters, digits, and underscores with the 
   restriction that they may not begin with a number.  

   Numeric literals are either a zero indicating zero value or a sequence of 
   digits beginning with any non-zero number.
 */  
ws                  [ \t\v\f\n]+
id                  [[:alpha:]_][[:alnum:]_]*
num                 0|[1-9][[:digit:]]*

%%
           
 /*
   Whitespace
   -----------------------------------------------------------------------------
   We just throw whitespace away.  As much as we can match at once.
 */
{ws}                ;

 /*
   Comments
   -----------------------------------------------------------------------------
   This approach follows the one used in the flex manual.  Comments may be
   arbitrarily long, so we match up to a line's worth at a time.  
 */

"/*"                BEGIN(COMMENT);
<COMMENT>{
[^*\n]*             /* Everything but asterisks and new lines            */;                 
"*"+([^*/]|\n)      /* String of asterisks that don't end comment        */;                    
"*"+"/"             /* End comment. Return to default state */     BEGIN(0);            
\n                  /* Match new lines in comments                       */;                   
<<EOF>>             /* Detect unterminated */          return E_EOF_COMMENT;
}

 /*
   Integer literals
   -----------------------------------------------------------------------------
   In our specified language only decimal integer literals are accepted.  Octal,
   hexadecimal integer literals and floating point literals are not accepted.  0
   takes on a somewhat odd behavior due to this specification.  Typically, octal
   literals  are prefixed with 0.  Because we are not accepting  octal literals,  
   each leading '0' encountered will be treated as a separate zero-valued const.

   Integer suffixes are also not accepted.  The size allocated for an integer 
   constant is the first from the following list  that can represent the integer
   without overflow (the list is taken from our language specification.)  Given 
   this rule and this list of types, we will never be using 'long' types.

   Type   Size in bytes
   - - -  - - - - - - -  
   char   1
   short  2
   int    4
   long   4
 */
{num}             { yylval = (YYSTYPE) make_integer(yytext);
                    return LITERAL_NUMBER; }

 /*
   Character literals
   -----------------------------------------------------------------------------
   A character constant is a single character enclosed within apostrophes.  In
   character constants we will allow octal and character escape codes.  Octal
   escape codes consist of a backslash followed by one, two, or three octal
   digits.  Character escape codes consist of a backslash followed by one of:
   n, t, b, r, f, v, \, ', ", a, and ?.  An unescaped double quote character
   is acceptable in a character literal. Per Harbison & Steele section 2.7.3, 
   character constants have type 'int'.
 */
"'"[[:print:]]{-}[\\\n\']"'" { yylval = (YYSTYPE) make_integer_from_char(yytext[1]);
                               return LITERAL_NUMBER; }

"''"                return E_BAD_LITERAL_CHAR;

"'\\''"           { yylval = (YYSTYPE) make_integer_from_char('\'');
                    return LITERAL_NUMBER; }
"'\\n'"           { yylval = (YYSTYPE) make_integer_from_char('\n');
                    return LITERAL_NUMBER; }
"'\\t'"           { yylval = (YYSTYPE) make_integer_from_char('\t');
                    return LITERAL_NUMBER; }
"'\\b'"           { yylval = (YYSTYPE) make_integer_from_char('\b');
                    return LITERAL_NUMBER; }
"'\\r'"           { yylval = (YYSTYPE) make_integer_from_char('\r');
                    return LITERAL_NUMBER; }
"'\\f'"           { yylval = (YYSTYPE) make_integer_from_char('\f');
                    return LITERAL_NUMBER; }
"'\\v'"           { yylval = (YYSTYPE) make_integer_from_char('\v');
                    return LITERAL_NUMBER; }
"'\\\\'"          { yylval = (YYSTYPE) make_integer_from_char('\\');
                    return LITERAL_NUMBER; }
"'\\\"'"          { yylval = (YYSTYPE) make_integer_from_char('\"'); 
                    return LITERAL_NUMBER; }
"'\\a'"           { yylval = (YYSTYPE) make_integer_from_char('\a');
                    return LITERAL_NUMBER; }
"'\\?'"           { yylval = (YYSTYPE) make_integer_from_char('\?');
                    return LITERAL_NUMBER; }

 /*
   Per Harbison & Steele section 2.7.3, character constants have type 'int', but
   are computed as if they have been converted from type 'char'.  H&S section
   5.1.3 specifies that it is up to the implementation to decide whether the 
   character type specifier 'char' means 'signed char' or 'unsigned char'. As
   no guidance is given in the Problem Set 1 specification, I've chosen:
   'char' => 'unsigned char'.  So, octal escape codes with values 255 and below 
   map to their value.  H&S section 2.7.7 indicates that values outside the
   range of 'unsigned char' are prohibited, so we'll return an error if this
   occurs.
 */
"'\\"[0-7]{1,3}"'" { yylval = (YYSTYPE) make_integer_from_octal(yytext); 
                     return LITERAL_NUMBER; } 
"'\\"[0-9]+"'"       return E_BAD_OCTAL_LITERAL;

 /* 
   Now that we have rules for all of the accepted character constants, we can
   mark anything else as a bad character literal.  Using a start condition here
   allows us to keep a single-quote 'open' across multiple lines and errors 
   until it is closed again.
 */
"'"                BEGIN(CHARACTER);
<CHARACTER>{
"'"                BEGIN(0);
[^\n\']+           return E_BAD_LITERAL_CHAR;
\n                 return E_UNTERM_CHAR;
<<EOF>>            return E_EOF_CHAR;
}
 
 /*
   String literals
   -----------------------------------------------------------------------------
   Strings literals are a sequence of any characters from the input character
   set enclosed in double quotes.  Backslash, double quote, and new line
   characters may be contained in a string literal but must be escaped.

   Character escape codes are permitted for n, t, b, r, f, v, ', ", \, a, and ?.
   Octal escape codes are permitted for one, two, or three digit octal literals.
   Octal values over LITERAL_CHAR_MAX are treated as overflow and recorded at
   LITERAL_CHAR_MAX.

   A single backslash may be used to continue a string from one line to the next
   When used in this fashion, the backslash must be the last character before 
   a new line.
 */
\"                { if (initialize_string_buffer()) return E_OUT_OF_MEMORY;
                    BEGIN(STRING); }

<STRING>{
\"                { yylval = (YYSTYPE) make_string();
                    BEGIN(0);
                    return LITERAL_STRING;}
\n                  return E_UNTERM_STR;
<<EOF>>             return E_EOF_STR;

"\\\'"              if (add_char_to_string_buffer('\'')) return E_OUT_OF_MEMORY;
"\\\""              if (add_char_to_string_buffer('\"')) return E_OUT_OF_MEMORY;
"\\n"               if (add_char_to_string_buffer('\n')) return E_OUT_OF_MEMORY;
"\\t"               if (add_char_to_string_buffer('\t')) return E_OUT_OF_MEMORY;
"\\b"               if (add_char_to_string_buffer('\b')) return E_OUT_OF_MEMORY;
"\\r"               if (add_char_to_string_buffer('\r')) return E_OUT_OF_MEMORY;
"\\f"               if (add_char_to_string_buffer('\f')) return E_OUT_OF_MEMORY;
"\\v"               if (add_char_to_string_buffer('\v')) return E_OUT_OF_MEMORY;
"\\\\"              if (add_char_to_string_buffer('\\')) return E_OUT_OF_MEMORY;
"\\a"               if (add_char_to_string_buffer('\a')) return E_OUT_OF_MEMORY;
"\\?"               if (add_char_to_string_buffer('\?')) return E_OUT_OF_MEMORY;

"\\"[0-7]{1,3}      if (add_octal_to_string_buffer(yytext)) return E_OUT_OF_MEMORY;
"\\"[0-9]+          return E_BAD_OCTAL_LITERAL;

"\\\n"              ;
"\\"                return E_BAD_CHAR_ESCAPE;

[[:print:]]{-}[\\\n\"]+  if (add_string_to_string_buffer(yytext, yyleng)) return E_OUT_OF_MEMORY;
}
                   
 /*
   Keywords
   -----------------------------------------------------------------------------
   Each keyword is represented  by a separate token value.  Keywords are matched
   before identifiers,  preventing them from being erroneously interpreted as
   identifier tokens.
 */

break               return BREAK;
char                return CHAR;
continue            return CONTINUE;  
do                  return DO;
else                return ELSE;
for                 return FOR;
goto                return GOTO;
if                  return IF;
int                 return INT;
long                return LONG;
return              return RETURN;
short               return SHORT;
signed              return SIGNED;
unsigned            return UNSIGNED;
void                return VOID;
while               return WHILE;

 /*
   Identifiers
   -----------------------------------------------------------------------------
   Now that we've matched all reserved words,  anything other lexemes that match
   {id} can be safely interpreted as identifiers
 */

{id}              { yylval = (YYSTYPE) make_id(yytext, yyleng);
                    return IDENTIFIER; }

"*"                 return ASTERISK;                
":"                 return COLON;                   
"-"                 return DASH;                    
"+"                 return PLUS;                    
"?"                 return QUESTION_MARK;           
"="                 return ASSIGN;                  
"&="                return ASSIGN_BITWISE_AND;
"|="                return ASSIGN_BITWISE_OR;     
"^="                return ASSIGN_BITWISE_XOR;      
"<<="               return ASSIGN_LEFT_SHIFT;     
">>="               return ASSIGN_RIGHT_SHIFT;      
"+="                return ASSIGN_SUM;     
"-="                return ASSIGN_DIFFERENCE;
"*="                return ASSIGN_PRODUCT;      
"/="                return ASSIGN_QUOTIENT;         
"%="                return ASSIGN_REMAINDER;        
"&"                 return BITWISE_AND;       
"|"                 return BITWISE_OR;              
"^"                 return BITWISE_XOR;             
"~"                 return BITWISE_NEGATION;        
"<<"                return LEFT_SHIFT;              
">>"                return RIGHT_SHIFT;             
"/"                 return DIVISION;                
"%"                 return REMAINDER;               
"++"                return INCREMENT;              
"--"                return DECREMENT;               
"<"                 return LESS;                
"<="                return LESS_OR_EQUAL;       
">"                 return GREATER;             
">="                return GREATER_OR_EQUAL;    
"=="                return EQUAL_TO;            
"!="                return NOT_EQUAL;           
"&&"                return LOGICAL_AND;             
"||"                return LOGICAL_OR;             
"!"                 return LOGICAL_NEGATION;        
"("                 return LEFT_PAREN;              
")"                 return RIGHT_PAREN;             
"["                 return LEFT_BRACKET;            
"]"                 return RIGHT_BRACKET;           
"{"                 return LEFT_BRACE;              
"}"                 return RIGHT_BRACE;             
";"                 return STATEMENT_TERMINATOR;   
","                 return SEQUENTIAL_EVAL;  

.                   return E_NO_MATCHING_TOKEN;

%%

/* make_id

   Creates a copy of provided string.

   Parameters   : string (char*)
                  - Location of string to be copied to new memory

                  length (int)
                  - Length of string to be copied

   Returns      : (char*) location of new copy of string.
                  NULL if new string cannot be allocated.

   Side-effects : Attempts to allocate memory on heap.
                  Copies data into allocated memory.
*/
char* make_id(const char* string, const int length)
{
  char* newString;

  newString = (char *) malloc(sizeof(char) * (length + 1));
  
  if (newString)
  {
    strcpy(newString, string);
  }

  return newString;
}

/* make_integer

   Parses an integer value from provided string.  Creates an integer instance
   carrying the parsed value, the suggested type for the value, and a flag that
   indicates if overflow occurred.

   Parameters   : string (char*)

   Returns      : integer* location of integer structure containing parsed
                  integer value, suggested type, and overflow indicator.
                  NULL if new integer cannot be allocated.

   Side-effects : Attempts to allocate memory on the heap.
                  Copies data into allocated memory.
*/
integer* make_integer(const char* string)
{
  integer* newInteger;

  newInteger = (integer*) malloc(sizeof(integer));
 
  if (!newInteger)
  {
    return newInteger;
  }
  
  errno = 0;
  newInteger->overflow_flag = NO_OVERFLOW;
  newInteger->value = strtoul(string, NULL, 10);

  /* We consider the overflow case first.  If the returned value is larger
     that our maximum integer, we set the value to our maximum integer and
     flag the overflow field.  If strtoul() overflows, it returns MAX_ULONG
     (as defined in <limits.h>) and sets errno to ERANGE.
  */
   
  if ((ERANGE == errno && ULONG_MAX == newInteger->value) || (newInteger->value > LITERAL_ULONG_MAX))
  {
    newInteger->value = LITERAL_ULONG_MAX;
    newInteger->type = LITERAL_ULONG;
    newInteger->overflow_flag = HAS_OVERFLOW;
  }

  /* If we aren't overflowing, we apply the logic from Harbison & Steele table
     2-5 to the table in our language spec.
  */ 
  else if (newInteger->value <= LITERAL_CHAR_MAX)
  {
    newInteger->type = LITERAL_CHAR;
  }
  else if (newInteger->value <= LITERAL_SHORT_MAX)
  {
    newInteger->type = LITERAL_SHORT;
  }
  else if (newInteger->value <= LITERAL_INT_MAX)
  {
    newInteger->type = LITERAL_INT;
  }
  else
  {
	newInteger->type = LITERAL_ULONG;
  }

  return newInteger;
}

/* make_integer_from_char

   Creates an integer from a character literal.  If character literal value
   comes from an octal literal, use make_integer_from_octal instead.

   Parameters   : charValue (int)
                  - numeric representation of a single literal character.

   Returns      : integer* location of integer_structure containing provided
                  value, suggested type (LITERAL_INT), and indication of no overflow.

   Side-effects : Attempts to allocate memory on the heap.
                  Copies data into allocated memory.
*/
integer* make_integer_from_char(const int charValue)
{
  integer* newInteger;
  newInteger = (integer*) malloc(sizeof(integer));

  if (!newInteger)
  {
    return newInteger;
  }

  newInteger->value = charValue;
  newInteger->type = LITERAL_INT;
  newInteger->overflow_flag = NO_OVERFLOW;

  return newInteger;
}

/* make_integer_from_octal

   Creates an integer from an octal literal.  While three digit octal literals
   are accepted, values larger than LITERAL_CHAR_MAX are not permitted and are
   flagged as overflow.

   Parameters   : string (char*)
                - string containing octal literal.  Either '\ or \ is expected
                  in the string before the 1-3 digit octal literal.
  
   Returns      : integer* location of integer structure containing parsed
                  value, suggested type (LITERAL_INT), and indication of overflow.  In
                  the case of overflow the parsed value is reported as 
                  LITERAL_CHAR_MAX.

   Side-effects : Attempts to allocate memory on the heap.
                  Copies data into allocated memory.
*/ 
integer* make_integer_from_octal(const char* text)
{
  integer* newInteger;
  unsigned long octalValue;

  /* 
     We're either getting an octal from a character constant or a string.
     The matched text for a character constant will start with a '\ we want to
     skip, while the matched text from a string constant will only start with \
     (which we also want to skip.)
  */
  int offset = (text[0] == '\'') ? 2 : 1;

  newInteger = (integer*) malloc(sizeof(integer));

  if (!newInteger)
  {
    return newInteger;
  }
  
  sscanf(text + offset, "%lo", &octalValue);
  newInteger->value = octalValue <= LITERAL_CHAR_MAX ? octalValue : LITERAL_CHAR_MAX;
  newInteger->overflow_flag = octalValue <= LITERAL_CHAR_MAX ? NO_OVERFLOW : HAS_OVERFLOW;
  newInteger->type = LITERAL_INT;
  return newInteger;
}

/* initialize_string_buffer

   Creates a new string buffer of size MAX_STR_LEN.  Resets the string buffer
   cursor to point to the start of the buffer.

   Parameters   : none

   Returns      : 0 if the buffer can be allocated
                  1 if the buffer cannot be allocated

   Side-effects : Attempts to allocate memory on the heap
                  Modifies address that string_buffer and string_buffer_cursor
                  point to.
 */
int initialize_string_buffer()
{
  if (!(string_buffer = malloc(MAX_STR_LEN*sizeof(char) + 1)))
  {
    return 1;
  }
  string_buffer_cursor = string_buffer;
  return 0;
}

/* remaining_buffer_capacity

   Convenience function to calculate the number of characters that may be
   appended to the string buffer before it is full.

   Parameters   : none

   Returns      : 0 if string_buffer is full or has not been allocated
                  Otherwise, returns number of characters left in 
                   string buffer.

   Side-effects : none
 */
int remaining_buffer_capacity()
{
  if (NULL == string_buffer)
  {
    return 0;
  }
  return MAX_STR_LEN - (string_buffer_cursor - string_buffer);
}

/* add_char_to_string_buffer

   Appends a single character to the string buffer

   Parameters   : charValue (const char)
                  - character to append to string buffer

   Returns      : 0 if character could be added, 
                  1 if character could not be added

   Side-effects : Memory at string_buffer_cursor may be changed,
                  Value of string_buffer_cursor may change.
*/
int add_char_to_string_buffer(const char charValue)
{
  if (remaining_buffer_capacity() > 1)
  {
    *string_buffer_cursor++ = charValue;
    return 0;
  }
  return 1;
}

/* add_octal_to_string_buffer

   Appends a single character to the string buffer.  Character is calculated
   from an octal literal.

   Parameters   : octalLiteral (const char*)
                  - A valid octal literal that will be parsed into an integer
                    value.  The integer value is then appended to the string
                    buffer.

   Returns      : 0 if character could be appended,
                  1 if character could not be appended

   Side-effects : Memory at string_buffer_cursor may be changed,
                  value of string_buffer_cursor may change.
*/
int add_octal_to_string_buffer(const char* octalLiteral)
{
  integer* integer;

  if (remaining_buffer_capacity() > 1)
  {
    integer = make_integer_from_octal(octalLiteral);
    if (!integer)
    {
      return 1;
    }
    *string_buffer_cursor++ = (unsigned char) integer->value;
    return 0;
  }
  return 1;
}

/* add_string_to_string_buffer

   Appends a string value to the string_buffer.

   Parameters   : string (const char*)
                  - string to append to string_buffer

                  length (const int)
                  - length of provided string

   Returns      : 1 if there isn't room in the string_buffer to hold
                  the provided string.  0 otherwise.

   Side-effects : The string_buffer_cursor is moved by the length of
                  the added string.  The string is copied into the 
                  string_buffer.
*/
int add_string_to_string_buffer(const char* string, const int length)
{
  if (remaining_buffer_capacity() > (length + 1))
  {
    strcpy(string_buffer_cursor, string);
    string_buffer_cursor += length;
    return 0;
  }
  return 1;
}

/* make_string

   Creates a new string and populates it with information about 
   the string_buffer.  

   Parameters   : none
   Returns      : New string containing pointer to string_buffer
                  as well as length and size data about string_buffer.
                  NULL if a new string cannot be allocated.

   Side-effects : Allocates memory on the heap.
                  Increments string_buffer_cursor.
                  Modifies string_buffer to add a terminating '\0'
*/
string* make_string()
{
  string* newString = malloc(sizeof(string));
  if (!newString)
  {
    return newString;
  }
  newString->length = string_buffer_cursor - string_buffer;
  newString->size = MAX_STR_LEN + 1;
 
  /* Zero-terminate string */
  *++string_buffer_cursor = '\0';
  newString->buffer = string_buffer;

  return newString;
}
