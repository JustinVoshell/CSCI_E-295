%{
#define YYSTYPE long int

  void *malloc_id(void);
  int eval_num(void);
  void *malloc_string(void);
%}

/* regular definitions */
delim   [ \t\n]
ws      {delim}+
letter  [A-Za-z]
digit   [0-9]
underscore _
id      ({letter}|{underscore})({letter}|{digit}|{underscore})*
number  {digit}+(\.{digit}*)?(E[+\-]?{digit}+)?
string  \"[^\"\n]*\"

%%

{ws}    {/* no action and no return */}
break   {return RW_BREAK;}
char    {return RW_CHAR;}
continue {return RW_CONTINUE;}
do      {return RW_DO;}
else    {return RW_ELSE;}
for     {return RW_FOR;}
goto    {return RW_GOTO;}
if      {return RW_IF;}
int     {return RW_INT;}
long    {return RW_LONG;}
return  {return RW_RETURN;}
short   {return RW_SHORT;}
signed  {return RW_SIGNED;}
unsigned {return RW_UNSIGNED;}
void    {return RW_VOID;}
while   {return RW_WHILE;}
{id}    {yylval = (long int)malloc_id(); return ID;}
{number} {yylval = eval_num(); return NUMBER;}
{string} {yylval = (long int)malloc_string(); return STRING;}
"("     {return PAREN_LEFT;}
")"     {return PAREN_RIGHT;}
"["     {return BRACKET_LEFT;}
"]"     {return BRACKET_RIGHT;}
"{"     {return BRACE_LEFT;}
"}"     {return BRACE_RIGHT;}
";"     {return STMTSEP_SEMICOLON;}
"++"    {return INCDEC_INCREMENT;}
"--"    {return INCDEC_DECREMENT;}
"!"     {return LOGNEG;}
"~"     {return BITWISENEG;}
"*"     {return MULOP_MULTIPLY;}
"/"     {return MULOP_DIVIDE;}
"%"     {return MULOP_REMAINDER;}
"+"     {return ADDOP_ADDITION;}
"-"     {return ADDOP_SUBTRACTION;}
"<<"    {return SHIFTOP_LEFT;}
">>"    {return SHIFTOP_RIGHT;}
"<"     {return RELOP_LT;}
"<="    {return RELOP_LE;}
">"     {return RELOP_GT;}
">="    {return RELOP_GE;}
"=="    {return EQUALOP_EQ;}
"<>"    {return EQUALOP_NE;}
"|"     {return BITWISEOP_OR;}
"^"     {return BITWISEOP_XOR;}
"&"     {return BITWISEOP_AND;}
"||"    {return LOGICALOP_OR;}
"&&"    {return LOGICALOP_AND;}
"?"     {return CONDITIONAL_QUEST;}
":"     {return CONDITIONAL_COLON;}
"="     {return ASSIGNOP_SIMPLE;}
"+="    {return ASSIGNOP_ADDITION;}
"-="    {return ASSIGNOP_SUBTRACTION;}
"*="    {return ASSIGNOP_MULTIPLICATION;}
"/="    {return ASSIGNOP_DIVISION;}
"%="    {return ASSIGNOP_REMAINDER;}
"<<="   {return ASSIGNOP_LEFTSHIFT;}
">>="   {return ASSIGNOP_RIGHTSHIFT;}
"&="    {return ASSIGNOP_BITWISEAND;}
"^="    {return ASSIGNOP_BITWISEXOR;}
"|="    {return ASSIGNOP_BITWISEOR;}
","     {return SEQUENTIALOP_COMMA;}

%%

#include <stdlib.h>
#include <string.h>

void *malloc_id(void) {
  char *id;

#ifdef DEBUG
  printf("malloc_id: Found id \"%s\" with length %d\n", yytext, yyleng);
  printf("malloc_id: yytext == 0x%8x\n", yytext);
#endif
  id = malloc(yyleng+1);
  if(id == (char *)NULL) {
    printf("***Out of memory***\n");
  } else {
    strcpy(id, yytext);
  }
#ifdef DEBUG
  printf("malloc_id: returning 0x%8x -> \"%s\"\n", id, id);
#endif
  return id;
}

int eval_num(void) {
  int val;

#ifdef DEBUG
  printf("eval_num: Found number \"%s\" with length %d\n", yytext, yyleng);
#endif
  val = strtoul(yytext, 0, 10);
  return val;
}

void *malloc_string(void) {
  char *str;

#ifdef DEBUG
  printf("malloc_string: Found string \"%s\" with length %d\n", yytext,
	 yyleng);
  printf("malloc_string: yytext == 0x%8x\n", yytext);
#endif
  str = malloc(yyleng+1);
  if(str == (char *)NULL) {
    printf("***Out of memory***\n");
  } else {
    strcpy(str, yytext);
  }
#ifdef DEBUG
  printf("malloc_str: returning 0x%8x -> \"%s\"\n", str, str);
#endif
  return str;
}
