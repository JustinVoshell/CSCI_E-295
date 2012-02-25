#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner/scanner_printer.h"

#include "model/codes.h"
#include "model/tokens.h"
#include "model/errors.h"

#define EXIT_OK 0
#define EXIT_OUT_OF_MEMORY 1

extern FILE* yyin;                      
int yylex();                            
extern char* yytext;                    
extern int yyleng;                      
extern int yylineno;                    
void* yylval;                           

FILE* output_;
const char* input_name_;

void open_(int argc, char** argv);
void close_();
int process_(const int token, void* attribute);

int main(int argc, char** argv)
{
	int scan_result;
	
	open_(argc, argv);
  codes_init();	

  for (scan_result = yylex(); 0 != scan_result; scan_result = yylex())
  {  
    if (scan_result !=0) sp_print_input(output_, input_name_, yylineno, yytext, yyleng);
    else break;

    if (scan_result > 0)
    {
      if (process_(scan_result, yylval)) return EXIT_OUT_OF_MEMORY;
    }
    else 
    {
			int error_code = (unsigned long)yylval;
      sp_print_error(output_, error_code);
      
			if (error_should_exit(error_code))
			{
        close_();
        return E_OUT_OF_MEMORY == error_code ? EXIT_OUT_OF_MEMORY : EXIT_OK;
      }
    }
  }

  close_();
  return EXIT_OK;
}

int process_(const int token, void* attribute)
{
  const char* token_name;

  if (!(token_name = codes_get(token)))
  {
    fprintf(output_, "ERROR: Unrecognized token: %i\n", token);
    return 0;
  }

  if (token_has_attribute(token)) 
  {
    if (!attribute)
    {
      sp_print_error(output_, E_OUT_OF_MEMORY);
      return EXIT_OUT_OF_MEMORY;
    }
  
  	if (IDENTIFIER == token)            sp_print_id(output_, (char*)attribute); 
  	else if (LITERAL_NUMBER == token)   sp_print_integer(output_, (integer*)attribute);
  	else if (LITERAL_STRING == token)   sp_print_string(output_, (string*)attribute);
  	free(attribute);
 	}
  else fprintf(output_, "%s\n", token_name);
  return 0;
}

void open_(int argc, char** argv)
{
  if (argc < 2 || !strcmp("-", argv[1])) 
  {
		input_name_ = "stdin";
    yyin = stdin;
  }
  else
  {
		input_name_ = argv[1];
    yyin = fopen(input_name_, "r");
  }

  if (argc < 3 || !strcmp("-", argv[2]))
  {
    output_ = stdout;
  }
  else
  {
    output_ = fopen(argv[2], "w");
  }
}

void close_()
{
  if (output_ != stdout) fclose(output_);
  if (yyin != stdin) fclose(yyin);
}