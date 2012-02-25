#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "code_table.h"
#include "tokens.h"
#include "integer_attribute.h"
#include "string_attribute.h"

#define MAX_INLINE_STRLEN 30
#define EXIT_OK 0
#define EXIT_OUT_OF_MEMORY 1

extern FILE* yyin;                      
int yylex();                            
extern char* yytext;                    
extern int yyleng;                      
extern int yylineno;                    
void* yylval;                           

const char* open_io(FILE** inputStream, const char* inputName, FILE** outputStream, const char* outputName);
void close_io(FILE* inputStream, FILE* outputStream);
int handle_token(const int token, void* attribute, FILE* output);
void fprint_id(FILE* output, const char* id);
void fprint_integer(FILE* output, const integer* integerData);
void fprint_string(FILE* output, const string* stringData);
void fprint_error(FILE* output, const unsigned long errorCode);
void fprint_lexeme(FILE* output, const char* inputName, const char* lexeme, const int lexemeLength, const int lineNumber);

int main(int argc, char** argv)
{
  FILE* input;
  FILE* output;
  
  int yylex_result;

  const char* inputName = open_io(&input, argc < 2 ? 0 : argv[1], &output, argc < 3 ? 0 : argv[2]);

  init_code_table();

  yyin = input;
  for (yylex_result = yylex(); 0 != yylex_result; yylex_result = yylex())
  {  
    if (yylex_result !=0)
    {
      fprint_lexeme(output, inputName, yytext, yyleng, yylineno);
    }
    else 
    {
      break;
    }

    if (yylex_result > 0)
    {
      if (handle_token(yylex_result, yylval, output)) return EXIT_OUT_OF_MEMORY;
    }
    else 
    {
			int error_code = (unsigned long)yylval;
      fprint_error(output, error_code);
      
			if (E_EOF_COMMENT == error_code
			    || E_EOF_STR == error_code
			    || E_EOF_CHAR == error_code 
			    || E_OUT_OF_MEMORY == error_code)
			{
        close_io(input, output);
        return E_OUT_OF_MEMORY == error_code ? EXIT_OUT_OF_MEMORY : EXIT_OK;
      }
    }
  }

  close_io(input, output);
  return EXIT_OK;
}

int handle_token(const int token, void* attribute, FILE* output)
{
  const char* token_name;

  if (!(token_name = decode(token)))
  {
    fprintf(output, "ERROR: Unrecognized token: %i\n", token);
    return 0;
  }

  if (IDENTIFIER == token || LITERAL_NUMBER == token || LITERAL_STRING == token) 
  {
    if (!attribute)
    {
      fprint_error(output, E_OUT_OF_MEMORY);
      return EXIT_OUT_OF_MEMORY;
    }
  
  	if (IDENTIFIER == token)            fprint_id(output, (char*)attribute); 
  	else if (LITERAL_NUMBER == token)   fprint_integer(output, (integer*)attribute);
  	else if (LITERAL_STRING == token)   fprint_string(output, (string*)attribute);
  	free(attribute);
 	}
  else fprintf(output, "%s\n", token_name);
  return 0;
}

void fprint_id(FILE* output, const char* id)
{
  fprintf(output, "%s: %s\n", decode(IDENTIFIER), id);
}

void fprint_integer(FILE* output, const integer* integer)
{
	fprintf(output, "%s\t", decode(LITERAL_NUMBER));
  fprintf(output, "VALUE: %-12lu\t", integer->value);
  fprintf(output, "TYPE: %-6s\t", decode(integer->type));
  fprintf(output, "%s\n", decode(integer->overflow_flag));
}

void fprint_string(FILE* output, const string* stringData) 
{
  size_t idx;

  if (stringData->length <= MAX_INLINE_STRLEN)
  {
    fputs("STRING: ", output);
    for (idx = 0; idx < stringData->length; idx++)
    {
      fputc(stringData->buffer[idx], output);
    }
    fputs("\n", output);
  }
  else
  {
    fputs("\nSTRING==>", output);
    for (idx = 0; idx < stringData->length; idx++)
    {
      fputc(stringData->buffer[idx], output);
    }
    fputs("<==STRING\n", output);
  }
}

void fprint_error(FILE* output, const unsigned long errorCode)
{
  const char* errorMessage;

  if ((errorMessage = decode(errorCode)))
  {
    fprintf(output, "ERROR: %s\n", errorMessage);
  }
  else
  {
    fprintf(output, "UNKNOWN ERROR\n");
  }
}

void fprint_lexeme(FILE* output, const char* inputName, const char* lexeme, const int lexemeLength, const int lineNo)
{
  fputs(inputName, output);
  fprintf(output, ":%i: ", lineNo);
  
  if (lexemeLength <= MAX_INLINE_STRLEN)
  {
    fprintf(output, "TEXT: %-30s\t", lexeme);
  }
  else
  {
    fprintf(output, "\nTEXT==>%s<==TEXT\n", lexeme);
  }
}

const char* open_io(FILE** inputStream, const char* inputName, FILE** outputStream, const char* outputName)
{
  if (!inputName || !strcmp("-", inputName)) 
  {
    *inputStream = stdin;
  }
  else
  {
    *inputStream = fopen(inputName, "r");
  }

  if (!outputName || !strcmp("-", outputName))
  {
    *outputStream = stdout;
  }
  else
  {
    *outputStream = fopen(outputName, "w");
  }

  return (stdin == *inputStream) ? "stdin" : inputName;
}

void close_io(FILE* input, FILE* output)
{
  if (output != stdout)
  {
    fclose(output);
  }
  if (input != stdin)
  {
    fclose(input);
  }
}