#include <stdio.h>
#include <string.h>

#include "node.h"
#include "parser_printer.h"

FILE *yyin;
FILE *output_file;

struct node *root_node;
int yyparse();

void yyerror(const char *error_message)
const char *input_filename;
extern int yylineno;

int main() 
{
  int result = 0;

  yyin = stdin;
  output_file = stdout;
  input_filename = "stdin";
	
  result = yyparse();
  if (!result) pp_print(root_node);
  return result;
}

void yyerror(const char *error_message)
{
  fprintf(stderr, "%s:%d: error: %s", input_filename, yylineno, error_message);
}
