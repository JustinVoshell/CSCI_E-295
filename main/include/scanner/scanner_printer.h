#ifndef SCANNER_PRINTER_H_JHV9902116
#define SCANNER_PRINTER_H_JHV9902116

#include <stdio.h>

#include "model/integer.h"
#include "model/string_buffer.h"

void sp_print_input(FILE* output, const char* input_name, const int line_number, const char* input_string, const int input_length);
void sp_print_id(FILE* output, const char* id);
void sp_print_integer(FILE* output, const integer* integer_data);
void sp_print_string(FILE* output, const string* string_data);
void sp_print_error(FILE* output, const unsigned long error_code);

#endif /*SCANNER_PRINTER_H_JHV9902116*/