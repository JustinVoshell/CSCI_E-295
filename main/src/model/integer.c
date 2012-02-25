#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "model/integer.h"

integer* integer_from_cstring(const char* string)
{
  integer* newInteger;

  newInteger = (integer*) malloc(sizeof(integer));

  if (!newInteger)
  {
    return newInteger;
  }

  errno = 0;
  newInteger->overflow_flag = NO_OVERFLOW;
  newInteger->value = strtoul(string, 0, 10);

  if ((ERANGE == errno && ULONG_MAX == newInteger->value) || (newInteger->value > LITERAL_ULONG_MAX))
  {
    newInteger->value = LITERAL_ULONG_MAX;
    newInteger->type = LITERAL_ULONG;
    newInteger->overflow_flag = HAS_OVERFLOW;
  }
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

integer* integer_from_char(const int charValue)
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

integer* integer_from_octal_char(const char* text)
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