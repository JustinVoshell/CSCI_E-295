#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "model/integer_data.h"

struct integer_data *integer_data_from_cstring(const char *string)
{
  struct integer_data *integer_data;

  integer_data = (struct integer_data *) malloc(sizeof(struct integer_data));
  if (!integer_data) return integer_data; 

  errno = 0;
  integer_data->overflow = INTEGER_DATA_NO_OVERFLOW;
  integer_data->value = strtoul(string, 0, 10);

  if ((ERANGE == errno && ULONG_MAX == integer_data->value) || (integer_data->value > INTEGER_DATA_UNSIGNED_LONG_MAX))
  {
    integer_data->value = 0;
    integer_data->type = INTEGER_DATA_UNSIGNED_LONG;
    integer_data->overflow = INTEGER_DATA_OVERFLOW;
  }
  else if (integer_data->value <= INTEGER_DATA_SIGNED_INT_MAX)
  {
    integer_data->type = INTEGER_DATA_SIGNED_INT;
  }
  else
  {
		integer_data->type = INTEGER_DATA_UNSIGNED_LONG;
  }

  return integer_data;
}

struct integer_data *integer_data_from_char(const int char_value)
{
  struct integer_data *integer_data;
  integer_data = (struct integer_data *) malloc(sizeof(struct integer_data));

  if (!integer_data) return integer_data;
  
  integer_data->value = char_value;
  integer_data->type = INTEGER_DATA_SIGNED_INT;
  integer_data->overflow = INTEGER_DATA_NO_OVERFLOW;

  return integer_data;
}

struct integer_data *integer_data_from_octal_char(const char *text)
{
  struct integer_data *integer_data;
  unsigned long octal_value;

  /* 
     We're either getting an octal from a character constant or a string.
     The matched text for a character constant will start with a '\ we want to
     skip, while the matched text from a string constant will only start with \
     (which we also want to skip.)
  */
  int offset = (text[0] == '\'') ? 2 : 1;

  integer_data = (struct integer_data *) malloc(sizeof(struct integer_data));

  if (!integer_data) return integer_data;
  
  sscanf(text + offset, "%lo", &octal_value);

  integer_data->value = octal_value <= INTEGER_DATA_UNSIGNED_CHAR_MAX ? octal_value : 0;
  integer_data->overflow = octal_value <= INTEGER_DATA_UNSIGNED_CHAR_MAX ? INTEGER_DATA_NO_OVERFLOW : INTEGER_DATA_OVERFLOW;
  integer_data->type = INTEGER_DATA_SIGNED_INT;

  return integer_data;
}