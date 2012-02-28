#include <stdio.h>

#include "node.h"
#include "parser_printer.h"

extern FILE *output_file;

void pp_array_declarator_(struct node *node)
{
  fputs("(", output_file);
  pp_print(node->data.array_declarator->declarator);
  fputs("[", output_file);
  if (node->data.array_declarator->length) pp_print(node->data.array_declarator->length);
  fputs("])", output_file);
}

void pp_declaration_(struct node *node)
{
  pp_print(node->data.declaration->type_specifier);
  fputs(" (", output_file);
  pp_print(node->data.declaration->declarator);
  fputs(");\n", output_file);
}

void pp_declaration_list_(struct node *node)
{
  if (node->data.list->next) 
  {
    pp_print(node->data.list->next);
  }
  pp_print(node->data.list->current);
}

void pp_error_(struct node *error)
{

}

void pp_declarator_list_(struct node* node, int add_comma)
{
  if (node->data.list->next)
  {
    pp_declarator_list_(node->data.list->next, 1);
  }
  pp_print(node->data.list->current);
  if (add_comma) fputs(", ", output_file);
}

void pp_function_declarator_(struct node *node)
{
	
}

void pp_identifier_(struct node *node)
{
  fprintf(output_file, "%s", node->data.name);
}

void pp_literal_string_(struct node *literal_string)
{
	
}

void pp_literal_integer_(struct node *literal_integer)
{
	
}

void pp_parameter_declaration_(struct node *node)
{
	
}

void pp_parameter_list_(struct node *node)
{
	
}

void pp_pointer_(struct node *node)
{
  fputs("(*", output_file);
  pp_print(node->data.pointer_to);
  fputs(")", output_file);
}

void pp_type_specifier_(struct node* node)
{
  const char *c_type_spec;
	
  switch(node->data.integer_type) {
  case INTEGER_TYPE_VOID           : { c_type_spec = "void";               break; }
  case INTEGER_TYPE_SIGNED_CHAR    : { c_type_spec = "signed char";        break; }
  case INTEGER_TYPE_UNSIGNED_CHAR  : { c_type_spec = "unsigned char";      break; }
  case INTEGER_TYPE_SIGNED_SHORT   : { c_type_spec = "signed short int";   break; }
  case INTEGER_TYPE_UNSIGNED_SHORT : { c_type_spec = "unsigned short int"; break; }
  case INTEGER_TYPE_SIGNED_INT     : { c_type_spec = "signed int";         break; }
  case INTEGER_TYPE_UNSIGNED_INT   : { c_type_spec = "unsigned int";       break; }
  case INTEGER_TYPE_SIGNED_LONG    : { c_type_spec = "signed long int";    break; }
  case INTEGER_TYPE_UNSIGNED_LONG  : { c_type_spec = "unsigned long int";  break; }
  default: break;
  }
  fputs(c_type_spec, output_file);
}

void pp_print(struct node *node)
{
  switch(node->node_type) {
  case NODE_ARRAY_DECLARATOR:      { pp_array_declarator_(node);      break; }
  case NODE_DECLARATION:           { pp_declaration_(node);           break; }
  case NODE_DECLARATION_LIST:      { pp_declaration_list_(node);      break; }
  case NODE_ERROR:                 { pp_error_(node);                 break; }
  case NODE_FUNCTION_DECLARATOR:   { pp_function_declarator_(node);   break; }
  case NODE_IDENTIFIER:            { pp_identifier_(node);            break; }
  case NODE_DECLARATOR_LIST:       { pp_declarator_list_(node, 0);    break; }
  case NODE_LITERAL_STRING:        { pp_literal_string_(node);        break; }
  case NODE_LITERAL_INTEGER:       { pp_literal_integer_(node);       break; }
  case NODE_PARAMETER_DECLARATION: { pp_parameter_declaration_(node); break; }
  case NODE_PARAMETER_LIST:        { pp_parameter_list_(node);        break; }
  case NODE_POINTER:               { pp_pointer_(node);               break; }
  case NODE_TYPE_SPECIFIER:        { pp_type_specifier_(node);        break; }
  default: break;
  }
}
