#include "scanner/scanner_printer.h"

#include "model/codes.h"
#include "model/tokens.h"
#include "model/errors.h"
#include "model/integer.h"
#include "model/string_buffer.h"

#define MAX_INLINE_STRLEN 30

void sp_print_input(FILE* output, const char* input_name, const int line_number, const char* input_string, const int input_length)
{
  fprintf(output, "%s:%i:", input_name, line_number);
  
  if (input_length <= MAX_INLINE_STRLEN)
  {
    fprintf(output, "%-30s\t", input_string);
  }
  else
  {
    fprintf(output, "\n==>\n%s\n<==\n", input_string);
  }
}

void sp_print_id(FILE* output, const char* id)
{
  fprintf(output, "%s: %s\n", codes_get(IDENTIFIER), id);
}

void sp_print_integer(FILE* output, const integer* integer)
{
	fprintf(output, "%s\t", codes_get(LITERAL_NUMBER));
  fprintf(output, "VALUE: %-12lu\t", integer->value);
  fprintf(output, "TYPE: %-6s\t", codes_get(integer->type));
  fprintf(output, "%s\n", codes_get(integer->overflow_flag));
}

void sp_print_string(FILE* output, const string* string_data) 
{
  size_t idx;

  if (string_data->length <= MAX_INLINE_STRLEN)
  {
    fprintf(output, "%s\t", codes_get(LITERAL_STRING));

    for (idx = 0; idx < string_data->length; idx++)
    {
      fputc(string_data->buffer[idx], output);
    }

    fputs("\n", output);
  }
  else
  {
    fputs("\nSTRING==>\n", output);

    for (idx = 0; idx < string_data->length; idx++)
    {
      fputc(string_data->buffer[idx], output);
    }

    fputs("\n<==STRING\n", output);
  }
}

void sp_print_error(FILE* output, const unsigned long error_code)
{
  const char* error_message;

  if ((error_message = codes_get(error_code)))
  {
    fprintf(output, "ERROR: %s\n", error_message);
  }
  else
  {
    fprintf(output, "UNKNOWN ERROR\n");
  }
}