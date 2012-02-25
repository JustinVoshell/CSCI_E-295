#include <string.h>

#include "model/string_buffer.h"
#include "model/integer.h"

char* string_buffer_ = 0;
char* string_buffer_cursor_ = 0;

int string_buffer_remaining_()
{
  if (0 == string_buffer_)
  {
    return 0;
  }
  return MAX_STR_LEN - (string_buffer_cursor_ - string_buffer_);
}
	
int string_buffer_init()
{
  if (!(string_buffer_ = malloc(MAX_STR_LEN*sizeof(char) + 1)))
  {
    return 1;
  }
  string_buffer_cursor_ = string_buffer_;
  return 0;
}

int string_buffer_add_char(const char charValue)
{
  if (string_buffer_remaining_() > 1)
  {
    *string_buffer_cursor_++ = charValue;
    return 0;
  }
  return 1;
}

int string_buffer_add_octal_char(const char* octalLiteral)
{
  integer* integer;

  if (string_buffer_remaining_() > 1)
  {
    integer = integer_from_octal_char(octalLiteral);
    if (!integer)
    {
      return 1;
    }
    *string_buffer_cursor_++ = (unsigned char) integer->value;
    return 0;
  }
  return 1;
}

int string_buffer_add_cstring(const char* string, const int length)
{
  if (string_buffer_remaining_() > (length + 1))
  {
    strcpy(string_buffer_cursor_, string);
    string_buffer_cursor_ += length;
    return 0;
  }
  return 1;
}

string* string_buffer()
{
  string* new_string = malloc(sizeof(string));
  if (!new_string)
  {
    return new_string;
  }
  new_string->length = string_buffer_cursor_ - string_buffer_;
  new_string->size = MAX_STR_LEN + 1;

  /* Zero-terminate string */
  *++string_buffer_cursor_ = '\0';
  new_string->buffer = string_buffer_;

  return new_string;
}