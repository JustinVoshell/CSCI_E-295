#ifndef JHV9902116_201202091015
#define JHV9902116_201202091015

#include <stddef.h>

/* token_attributes.h
   Justin Voshell - justin.voshell@me.com
   CSCI E-295 Spring 2012
  
   Defines structured types for returning token attribute data.
   Defines max sizes for integer data types. 
*/

/*
   integer_representation

   An enumeration of the different ways we may represent an integer constant.
*/
typedef enum
{
  LITERAL_CHAR = 10,
  LITERAL_SHORT,
	LITERAL_INT,
	LITERAL_ULONG
} integer_representation;

typedef enum
{
	NO_OVERFLOW = 0,
	HAS_OVERFLOW
} overflow;

/* integer

   A structure for storing integer constants.  Holds the acutal integer value in
   an unsigned long.  Carries a value indicating the correct type to use for the 
   integer as well as a value indicating if an overflow was encountered.
*/
typedef struct
{
  unsigned long value;
	integer_representation type;
  overflow overflow_flag;
} integer;

/*
	Max values for different integer representations
*/
#define LITERAL_CHAR_MAX           255 /* Our target char is 8 bit           */
#define LITERAL_SHORT_MAX        65535 /* Our target short is 16 bit         */            
#define LITERAL_INT_MAX     2147483647 /* Our target int is signed 32 bit    */
#define LITERAL_ULONG_MAX 4294967295ul /* Our target unsigned long is 32 bit */

/* string

   A structure for describing a string buffer.  Holds a pointer to the start of 
   the buffer and carries two values giving the size of the buffer and the
   length of the string contained in the buffer
*/
typedef struct
{
  char* buffer;
  size_t length;
  size_t size;
} string;

#endif