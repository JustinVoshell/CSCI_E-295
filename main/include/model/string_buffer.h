#ifndef STRING_BUFFER_H_JHV9902116
#define STRING_BUFFER_H_JHV9902116

#include <stdlib.h>

#define MAX_STR_LEN 65535

typedef struct
{
  char* buffer;
  size_t length;
  size_t size;
} string;

int string_buffer_init();

int string_buffer_add_char(const char charValue);
int string_buffer_add_octal_char(const char* octalLiteral);
int string_buffer_add_cstring(const char* string, const int length);

string* string_buffer();

#endif /*STRING_BUFFER_H_JHV9902116*/
