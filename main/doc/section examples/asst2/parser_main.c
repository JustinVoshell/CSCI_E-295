#include <stdio.h>
#include <string.h>

#include "node.h"

FILE *yyin;
int yyparse();
extern int yynerrs;
node *root_node;
FILE *error_output;

int main(int argc, char **argv) {
  FILE *input, *output;
  int result;
  /* figure out whether we're using stdin/stdout or file in/file out */
  if (argc < 2 || !strcmp("-", argv[1])) {
    input = stdin;
  } else {
    input = fopen(argv[1], "r");
  }
  
  
  /* tell lex where to get input */
  yyin = input;
  error_output = stderr;
  
  result = yyparse();
  
  if (yynerrs > 0) {
    result = 1;
  }
  switch (result) {
    case 0:
      if (argc < 3 || !strcmp("-", argv[2])) {
        output = stdout;
      } else {
        output = fopen(argv[2], "w");
      }
      fputs("\n", output);
      print_node(output, root_node);
      fputs("\n", output);
      break;
      
    case 1:
      fprintf(stderr, "parser encountered %d error%s\n", yynerrs, (yynerrs == 1 ? "" : "s"));
      break;
      
    case 2:
      fprintf(stderr, "parser ran out of memory\n");
      break;
  }
  return result;
}
