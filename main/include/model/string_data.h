#ifndef STRING_DATA_H_JHV9902116
#define STRING_DATA_H_JHV9902116

#define STRING_BUFFER_LENGTH 65534

struct string_data
{
  char* buffer;
  unsigned short length;
  unsigned short size;
};

int string_data_new_buffer();
int string_data_add_char(const char value);
int string_data_add_octal_char(const char *octal_escape);
int string_data_add_cstring(const char *cstring, const int length);

struct string_data *string_data_from_buffer();

#endif /*STRING_DATA_H_JHV9902116*/