#include <stdio.h>

#include "model/node.h"
#include "model/tokens.h"
#include "model/resource.h"

#include "scanner/scanner_printer.h"

#define MAX_INLINE_STRLEN 30

extern FILE *output_file;
extern const char *input_filename;

void sp_print_error(const enum error_type error_type)
{
	const char* error_message = resource(error_type);

  if (error_message)
  {
    fprintf(output_file, "ERROR: %s\n", error_message);
  }
  else
  {
    fputs("UNKNOWN ERROR\n", output_file);
  }
}

void sp_print_input(const int line_number, const char* input_string, const int input_length)
{
  fprintf(output_file, "%s:%i:", input_filename, line_number);
  
  if (input_length <= MAX_INLINE_STRLEN)
  {
    fprintf(output_file, "%-30s\t", input_string);
  }
  else
  {
    fprintf(output_file, "\n==>\n%s\n<==\n", input_string);
  }
}

void sp_print_id_(const struct node *node)
{
  fprintf(output_file, "%s: %s\n", resource(IDENTIFIER), node->data.cstring_value);
}

void sp_print_integer_(const struct node *node)
{
	fprintf(output_file, "%s\t",            resource(LITERAL_NUMBER));
  fprintf(output_file, "VALUE: %-12lu\t", node->data.integer_data->value);
  fprintf(output_file, "TYPE: %-6s\t",    resource(node->data.integer_data->type));
  fprintf(output_file, "%s\n",            resource(node->data.integer_data->overflow));
}

void sp_print_string_(const struct node *node) 
{
  unsigned short idx;
	const char *string_type_name = resource(LITERAL_STRING);
	
  if (node->data.string_data->length <= MAX_INLINE_STRLEN)
  {
    fprintf(output_file, "%s\t", string_type_name);
    for (idx = 0; idx < node->data.string_data->length; idx++)
    {
      fputc(node->data.string_data->buffer[idx], output_file);
    }
    fputs("\n", output_file);
  }
  else
  {
    fprintf(output_file, "\n%s==>\n", string_type_name);
    for (idx = 0; idx < node->data.string_data->length; idx++)
    {
      fputc(node->data.string_data->buffer[idx], output_file);
    }
    fprintf(output_file, "\n<==%s\n", string_type_name);
  }
}

void sp_print_node(const struct node* node)
{
	switch (node->node_type)
	{
		case NODE_ERROR:           { sp_print_error(node->data.error_type);   break; }

		case NODE_IDENTIFIER:      { sp_print_id_(node);      break; }
		case NODE_LITERAL_INTEGER: { sp_print_integer_(node); break; }
		case NODE_LITERAL_STRING:  { sp_print_string_(node);  break; }

		default: break;
	}
}