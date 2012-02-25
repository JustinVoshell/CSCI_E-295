#include <string.h>

#include "integer_attribute.h"
#include "string_attribute.h"

char* string_buffer = 0;
char* string_buffer_cursor = 0;

int remaining_buffer_capacity()
{
  if (0 == string_buffer)
  {
    return 0;
  }
  return MAX_STR_LEN - (string_buffer_cursor - string_buffer);
}
	
int initialize_string_buffer()
{
  if (!(string_buffer = malloc(MAX_STR_LEN*sizeof(char) + 1)))
  {
    return 1;
  }
  string_buffer_cursor = string_buffer;
  return 0;
}

int add_char(const char charValue)
{
  if (remaining_buffer_capacity() > 1)
  {
    *string_buffer_cursor++ = charValue;
    return 0;
  }
  return 1;
}

int add_octal_char(const char* octalLiteral)
{
  integer* integer;

  if (remaining_buffer_capacity() > 1)
  {
    integer = integer_from_octal_char(octalLiteral);
    if (!integer)
    {
      return 1;
    }
    *string_buffer_cursor++ = (unsigned char) integer->value;
    return 0;
  }
  return 1;
}

int add_cstring(const char* string, const int length)
{
  if (remaining_buffer_capacity() > (length + 1))
  {
    strcpy(string_buffer_cursor, string);
    string_buffer_cursor += length;
    return 0;
  }
  return 1;
}

string* string_from_buffer()
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