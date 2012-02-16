#include <stdio.h>
#include "lexer.h"

char *str_resvword[] = {"break", "char", "continue", "do", "else", "for",
			 "goto", "if", "int", "long", "return", "short",
			 "signed", "unsigned", "void", "while"};
char *str_paren[] = {"(", ")"};
char *str_bracket[] = {"[", "]"};
char *str_brace[] = {"{", "}"};
char *str_stmtsep[] = {";"};
char *str_incdec[] = {"++", "--"};
char *str_logneg[] = {"!"};
char *str_bitwiseneg[] = {"~"};
char *str_mulop[] = {"*", "/", "%"};
char *str_addop[] = {"+", "-"};
char *str_shiftop[] = {"<<", ">>"};
char *str_relop[] = {"<", "<=", ">", ">="};
char *str_equalop[] = {"==", "!="};
char *str_bitwiseop[] = {"|", "^", "&"};
char *str_logicalop[] = {"||", "&&"};
char *str_conditional[] = {"?", ":"};
char *str_assignop[] = {"=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=",
                        "&=", "^=", "|="};
char *str_sequentialop[] = {","};

long int yylval;

int main(int argc, char *argv[]) {
  int token;

  while(!feof(stdin)) {
    token = yylex();
    if(feof(stdin))
      break;
    switch(token) {
    case RESVWORD:
      printf("main: case RESVWORD: %s\n", str_resvword[yylval]);
      break;
    case ID:
      printf("main: case ID: ");
      if(yylval == (long int)NULL) {
	printf("***Out of memory***\n");
      } else {
	printf("%s\n", (char *)yylval);
      }
#ifdef DEBUG
      printf("main: yylval == 0x%8lx -> \"%s\"\n", yylval, (char *)yylval);
#endif
      break;
    case NUMBER:
      printf("main: case NUMBER: %ld\n", yylval);
      break;
    case STRING:
      printf("main: case STRING: ");
      if(yylval == (long int)NULL) {
	printf("***Out of memory***\n");
      } else {
	printf("%s\n", (char *)yylval);
      }
#ifdef DEBUG
      printf("main: yylval == 0x%8lx -> \"%s\"\n", yylval, (char *)yylval);
#endif
      break;
    case PAREN:
      printf("main: case PAREN: %s\n", str_paren[yylval]);
      break;
    case BRACKET:
      printf("main: case BRACKET: %s\n", str_bracket[yylval]);
      break;
    case BRACE:
      printf("main: case BRACE: %s\n", str_brace[yylval]);
      break;
    case STMTSEP:
      printf("main: case STMTSEP: %s\n", str_stmtsep[yylval]);
      break;
    case INCDEC:
      printf("main: case INCDEC: %s\n", str_incdec[yylval]);
      break;
    case LOGNEG:
      printf("main: case LOGNEG: %s\n", str_logneg[yylval]);
      break;
    case BITWISENEG:
      printf("main: case BITWISENEG: %s\n", str_bitwiseneg[yylval]);
      break;
    case MULOP:
      printf("main: case MULOP: %s\n", str_mulop[yylval]);
      break;
    case ADDOP:
      printf("main: case ADDOP: %s\n", str_addop[yylval]);
      break;
    case SHIFTOP:
      printf("main: case SHIFTOP: %s\n", str_shiftop[yylval]);
      break;
    case RELOP:
      printf("main: case RELOP: %s\n", str_relop[yylval]);
      break;
    case EQUALOP:
      printf("main: case EQUALOP: %s\n", str_equalop[yylval]);
      break;
    case BITWISEOP:
      printf("main: case BITWISEOP: %s\n", str_bitwiseop[yylval]);
      break;
    case LOGICALOP:
      printf("main: case LOGICALOP: %s\n", str_logicalop[yylval]);
      break;
    case CONDITIONAL:
      printf("main: case CONDITIONAL: %s\n", str_conditional[yylval]);
      break;
    case ASSIGNOP:
      printf("main: case ASSIGNOP: %s\n", str_assignop[yylval]);
      break;
    case SEQUENTIALOP:
      printf("main: case SEQUENTIALOP: %s\n", str_sequentialop[yylval]);
      break;
    default:
      printf("yylex returned %d; yylval = %ld\n", token, yylval);
      break;
    }
  }
  return 0;
}

int yywrap(void) {
  return 1;
}
