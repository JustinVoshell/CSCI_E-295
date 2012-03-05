#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "model/node.h"
#include "model/resource.h"

#include "parse.h" 
#include "parser/debug_printer.h"
#include "parser/parser_printer.h"

/* 'YY' interface */
FILE *yyin;
int yyparse();  
extern YYLTYPE yylloc;
extern int yydebug;

/* 'Public' */
const char* input_filename;
const char* output_filename;
FILE *output_file;
struct node *root_node;

/* 'Private' */
int parser_errorc_ = 0;
int parser_opts_(int argc, char** argv);
void parser_init_();
void parser_dispose_();
int (*parser_print_)(struct node*);

void yyerror(const char *message)
{
	fprintf(stderr, "%s:%d.%d-%d.%d: error: %s\n", 
    input_filename, 
    yylloc.first_line, yylloc.first_column,
    yylloc.last_line, yylloc.last_column,
    message);
  
  parser_errorc_++;
}
          
int main(int argc, char **argv) 
{
	int yyparse_result = 0;
	
	if (parser_opts_(argc, argv))
	{
		fprintf(stderr, 
		"usage: parser [options] [input-file] [output-file]\n \
-i input-file.  default value is stdin.\n \
-o output-file. default value is stdout.\n \
-t use tree printer instead of default C syntax printer\n \
-d turn on Bison debugging output.\n\n");
		return 1;
	}
	
  parser_init_();
  resource_init();
         
	yyparse_result = yyparse();
	if (!yyparse_result && parser_errorc_ == 0) 
  {
		(*parser_print_)(root_node);
  }
  
	fputs("\n", output_file);
  parser_dispose_();

  return yyparse_result;
}

int parser_opts_(int argc, char **argv)
{                                                
	int option;
	const char* options = "tdi:o:"; 
	int optionIndex;
	
	/* Default values */
	input_filename = "stdin";
	output_filename = "stdout"; 
	parser_print_ = &pp_print;
	yydebug = 0;
  
	/* Get options */
	opterr = 1;
	while ((option = getopt(argc, argv, options)) != -1)
	{
		switch (option)
		{
			case 'i': input_filename = optarg;       break;
			case 'o': output_filename = optarg;      break;
			case 't': parser_print_ = &debug_print;  break;
			case 'd': yydebug = 1;                   break;
			
			case '?':
				if (isprint(optopt))
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character '\\x%x.\n", optopt);
				return 1;
			
			default: return 1;
		}
	}
	                 
	/* Handle input-file / output-file arguments */
	optionIndex = optind;
	if (optionIndex < argc) input_filename  = argv[optionIndex++];
	if (optionIndex < argc) output_filename = argv[optionIndex];
	
	return 0;                      
}

void parser_init_()
{
  if (!strcmp(input_filename, "stdin")) 
    yyin = stdin;
  else
    yyin = fopen(input_filename, "r");


	if (!strcmp(output_filename, "stdout"))
    output_file = stdout;
  else
    output_file = fopen(output_filename, "w");
}

void parser_dispose_()
{
  if (yyin != stdin) fclose(yyin);
  if (output_file != stdout) fclose(output_file);
}