#ifndef STRING_ATTRIBUTE_H
#define STRING_ATTRIBUTE_H

#include <stdlib.h>

#define MAX_STR_LEN 65535

typedef struct
{
  char* buffer;
  size_t length;
  size_t size;
} string;

int initialize_string_buffer();

int add_char(const char charValue);
int add_octal_char(const char* octalLiteral);
int add_cstring(const char* string, const int length);

string* string_from_buffer();

#endif /*STRING_ATTRIBUTE_H*/