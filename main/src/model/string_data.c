#include <stdlib.h>
#include <string.h>

#include "model/node.h"
#include "model/string_data.h"
#include "model/integer_data.h"

char* string_buffer_ = 0;
char* string_buffer_cursor_ = 0;

int string_buffer_remaining_()
{
  if (0 == string_buffer_)
  {
    return 0;
  }
  return STRING_BUFFER_LENGTH - (string_buffer_cursor_ - string_buffer_);
}
	
int string_data_new_buffer()
{
  if (!(string_buffer_ = malloc((STRING_BUFFER_LENGTH * sizeof(char) )+ 1)))
  {
    return 1;
  }
  string_buffer_cursor_ = string_buffer_;
  return 0;
}

int string_data_add_char(const char charValue)
{
  if (string_buffer_remaining_() > 1)
  {
    *string_buffer_cursor_++ = charValue;
    return 0;
  }
  return 1;
}

int string_data_add_octal_char(const char* octalLiteral)
{
  struct integer_data *integer;

  if (string_buffer_remaining_() > 1)
  {
    integer = integer_data_from_octal_char(octalLiteral);
    if (!integer)
    {
      return 1;
    }
    *string_buffer_cursor_++ = (unsigned char) integer->value;
    return 0;
  }
  return 1;
}

int string_data_add_cstring(const char* string, const int length)
{
  if (string_buffer_remaining_() > (length + 1))
  {
    strcpy(string_buffer_cursor_, string);
    string_buffer_cursor_ += length;
    return 0;
  }
  return 1;
}

struct string_data *string_data_from_buffer()
{
  struct string_data *new_string = malloc(sizeof(struct string_data));
  if (!new_string)
  {
    return new_string;
  }
  new_string->length = string_buffer_cursor_ - string_buffer_;
  new_string->size = STRING_BUFFER_LENGTH + 1;

  /* Zero-terminate string */
  *++string_buffer_cursor_ = '\0';
  new_string->buffer = string_buffer_;

  return new_string;
}