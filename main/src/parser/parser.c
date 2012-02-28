#include <stdio.h>
#include <string.h>

#include "model/node.h"
#include "parser/parser_printer.h"

FILE *yyin;
FILE *output_file;

const char* input_filename;
extern int yylineno;

struct node *root_node;
int yyparse();

int main(int argc, char **argv) 
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
