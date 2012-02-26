#include <stdio.h>
#include <string.h>

#include "model/node.h"
#include "parser/parser_printer.h"

FILE *yyin;
int yyparse();
struct node *root_node;
FILE *parser_output;
const char* parser_input_name;

int main(int argc, char **argv) {
  int result;

  /* tell lex where to get input */
  yyin = stdin;
	parser_output = stdout;
	parser_input_name = "stdin";
	
	result = yyparse();
	if (!result)
	{
		pp_print(root_node);
	}

  return result;
}