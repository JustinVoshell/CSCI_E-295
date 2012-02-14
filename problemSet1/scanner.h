#ifndef JHV9902116_201202091015
#define JHV9902116_201202091015

#include <stddef.h>

/* scanner.h
   Justin Voshell - justin.voshell@me.com
   CSCI E-295 Spring 2012
  
   Defines structured types for returning token attribute data.
   Defines max sizes for integer data types. 
*/
   
/* integer_t

   A structure for storing integer constants.  Holds the acutal integer value in
   an unsigned long.  Carries a value indicating the correct type to use for the 
   integer as well as a value indicating if an overflow was encountered.
*/
typedef struct integer_t_
{
  unsigned long value;
  int type;
  int overflow;
} integer_t;

/* string_t

   A structure for describing a string buffer.  Holds a pointer to the start of 
   the buffer and carries two values giving the size of the buffer and the
   length of the string contained in the buffer
*/
typedef struct string_t_
{
  char* buffer;
  size_t length;
  size_t size;
} string_t;

#define E295_CHAR_MAX           255       /* Our target char is 8 bit           */
#define E295_SHORT_MAX        65535       /* Our target short is 16 bit         */            
#define E295_INT_MAX   4294967295ul       /* Our target int is 32 bit           */

#endif
