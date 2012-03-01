#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner/scanner_printer.h"

#include "model/node.h"
#include "model/resource.h"
#include "model/tokens.h"
#include "model/error_type.h"

#define EXIT_OK 0
#define EXIT_OUT_OF_MEMORY 1

int yylex();                            
extern FILE *yyin;                      
extern char *yytext;                    
extern int yyleng;                      
extern int yylineno;                    
struct node *yylval;                           

FILE *output_file;
const char *input_filename;

void open_(int argc, char **argv);
void close_();
int process_(const int token, struct node *attribute);
int token_has_attribute_(const int token);

int main(int argc, char **argv)
{
	int scan_result;
	
	open_(argc, argv);
  resource_init();	

  for (scan_result = yylex(); 0 != scan_result; scan_result = yylex())
  {  
		if (scan_result <=0) break;
		
		sp_print_input(yylineno, yytext, yyleng);
    if (process_(scan_result, yylval)) return EXIT_OUT_OF_MEMORY;

		if (SCANNER_ERROR == scan_result && error_type_requires_exit(yylval->data.error_type)) break;
	}

  close_();
  return EXIT_OK;
}

int process_(const int token, struct node *attribute)
{
  const char* token_name;

  if (!(token_name = resource(token)))
  {
    fprintf(output_file, "ERROR: Unrecognized token: %i\n", token);
    return 0;
  }

  if (token_has_attribute_(token)) 
  {
    if (!attribute)
    {
      sp_print_error(ERROR_OUT_OF_MEMORY);
      return EXIT_OUT_OF_MEMORY;
    }
		sp_print_node(attribute);
 	}
  else
	{
		fprintf(output_file, "%s\n", token_name);
	}
  return 0;
}

int token_has_attribute_(const int token)
{
	return (IDENTIFIER == token ||
					LITERAL_STRING == token ||
					LITERAL_NUMBER == token) ? 1 : 0;
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
    output_file = stdout;
  }
  else
  {
    output_file = fopen(argv[2], "w");
  }
}

void close_()
{
  if (output_file != stdout) fclose(output_file);
  if (yyin != stdin) fclose(yyin);
}