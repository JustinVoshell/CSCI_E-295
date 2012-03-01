#include <stdio.h>
#include <string.h>

#include "model/node.h"
#include "parser/parser_printer.h"

FILE *yyin;
FILE *output_file;

const char* input_filename;
const char* output_filename;

extern int yylineno;
extern int yydebug;

struct node *root_node;
int yyparse();

void open_(int argc, char** argv);
void close_();

int main(int argc, char **argv) 
{
  int result;
  open_(argc, argv);

	result = yyparse();
	if (!result) 
  {
    pp_print(root_node);
    fputs("\n\n", output_file);
  }
  
  close_();
  return result;
}

void yyerror(const char *error_message)
{
	fprintf(stderr, "%s:%d: error: %s", input_filename, yylineno, error_message);
}

void open_(int argc, char** argv)
{
  if (argc < 2 || !strcmp("-", argv[1])) 
  {
		input_filename = "stdin";
    yyin = stdin;
  }
  else
  {
		input_filename = argv[1];
    yyin = fopen(input_filename, "r");
  }

  if (argc < 3 || !strcmp("-", argv[2]))
  {
    output_filename = "stdout";
    output_file = stdout;
  }
  else
  {
    output_filename = argv[2];
    output_file = fopen(output_filename, "w");
  }
}

void close_()
{
  if (output_file != stdout) fclose(output_file);
  if (yyin != stdin) fclose(yyin);
}