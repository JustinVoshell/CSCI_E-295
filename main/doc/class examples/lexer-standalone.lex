%{
#include "lexer.h"

  extern long int yylval;
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
break   {yylval = RW_BREAK; return RESVWORD;}
char    {yylval = RW_CHAR; return RESVWORD;}
continue {yylval = RW_CONTINUE; return RESVWORD;}
do      {yylval = RW_DO; return RESVWORD;}
else    {yylval = RW_ELSE; return RESVWORD;}
for     {yylval = RW_FOR; return RESVWORD;}
goto    {yylval = RW_GOTO; return RESVWORD;}
if      {yylval = RW_IF; return RESVWORD;}
int     {yylval = RW_INT; return RESVWORD;}
long    {yylval = RW_LONG; return RESVWORD;}
return  {yylval = RW_RETURN; return RESVWORD;}
short   {yylval = RW_SHORT; return RESVWORD;}
signed  {yylval = RW_SIGNED; return RESVWORD;}
unsigned {yylval = RW_UNSIGNED; return RESVWORD;}
void    {yylval = RW_VOID; return RESVWORD;}
while   {yylval = RW_WHILE; return RESVWORD;}
{id}    {yylval = (long int)malloc_id(); return ID;}
{number} {yylval = eval_num(); return NUMBER;}
{string} {yylval = (long int)malloc_string(); return STRING;}
"("     {yylval = PARENLEFT; return PAREN;}
")"     {yylval = PARENRIGHT; return PAREN;}
"["     {yylval = BRACKETLEFT; return BRACKET;}
"]"     {yylval = BRACKETRIGHT; return BRACKET;}
"{"     {yylval = BRACELEFT; return BRACE;}
"}"     {yylval = BRACERIGHT; return BRACE;}
";"     {yylval = SEPSEMICOLON; return STMTSEP;}
"++"    {yylval = INCDECINCREMENT; return INCDEC;}
"--"    {yylval = INCDECDECREMENT; return INCDEC;}
"!"     {yylval = 0; return LOGNEG;}
"~"     {yylval = 0; return BITWISENEG;}
"*"     {yylval = MULTIPLY; return MULOP;}
"/"     {yylval = DIVIDE; return MULOP;}
"%"     {yylval = REMAINDER; return MULOP;}
"+"     {yylval = ADDITION; return ADDOP;}
"-"     {yylval = SUBTRACTION; return ADDOP;}
"<<"    {yylval = LEFT; return SHIFTOP;}
">>"    {yylval = RIGHT; return SHIFTOP;}
"<"     {yylval = LT; return RELOP;}
"<="    {yylval = LE; return RELOP;}
">"     {yylval = GT; return RELOP;}
">="    {yylval = GE; return RELOP;}
"=="    {yylval = EQ; return EQUALOP;}
"<>"    {yylval = NE; return EQUALOP;}
"|"     {yylval = BITOR; return BITWISEOP;}
"^"     {yylval = BITXOR; return BITWISEOP;}
"&"     {yylval = BITAND; return BITWISEOP;}
"||"    {yylval = LOGICALOR; return LOGICALOP;}
"&&"    {yylval = LOGICALAND; return LOGICALOP;}
"?"     {yylval = CONDQUEST; return CONDITIONAL;}
":"     {yylval = CONDCOLON; return CONDITIONAL;}
"="     {yylval = ASSIGNMENTSIMPLE; return ASSIGNOP;}
"+="    {yylval = ASSIGNMENTADDITION; return ASSIGNOP;}
"-="    {yylval = ASSIGNMENTSUBTRACTION; return ASSIGNOP;}
"*="    {yylval = ASSIGNMENTMULTIPLICATION; return ASSIGNOP;}
"/="    {yylval = ASSIGNMENTDIVISION; return ASSIGNOP;}
"%="    {yylval = ASSIGNMENTREMAINDER; return ASSIGNOP;}
"<<="   {yylval = ASSIGNMENTLEFTSHIFT; return ASSIGNOP;}
">>="   {yylval = ASSIGNMENTRIGHTSHIFT; return ASSIGNOP;}
"&="    {yylval = ASSIGNMENTBITWISEAND; return ASSIGNOP;}
"^="    {yylval = ASSIGNMENTBITWISEXOR; return ASSIGNOP;}
"|="    {yylval = ASSIGNMENTBITWISEOR; return ASSIGNOP;}
","     {yylval = SEQUENTIALCOMMA; return SEQUENTIALOP;}

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
