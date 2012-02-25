%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <limits.h>

	#include "tokens.h"
	#include "code_table.h"
  #include "integer_attribute.h"
  #include "string_attribute.h"
 
  #define YYSTYPE void*
  extern YYSTYPE yylval;
	void yyerror(const char* message);
	
	int yy_integer_from_char(const char);
	int yy_integer_from_cstring(const char*);
	int yy_integer_from_octal_char(const char*);
	
	int yy_begin_string();
	int yy_end_string();
	
	int yy_id(const char* text, const int length);
	int yy_token(const int tokenValue);
	int yy_error(const int code);
%}

%option yylineno                        
%option nounput                         
%option yywrap                          

 /* 
	Start conditions: X (comment), S (string), BAD_CHAR (invalid character const) 
 */ 

%x X
%x S
%x BAD_CHAR

ws                  					[ \t\v\f\n]+
id                  					[[:alpha:]_][[:alnum:]_]*
num                 					0|[1-9][[:digit:]]*
comment_begin									\/\*
comment_end									  \*?\*\/
comment_body                  [^*\n]*
comment_bodyStars             \*+([^*/]|\n)
octal_literal									\\[0-7]{1,3}
bad_octal_literal							  \\[0-9]+
string_char                    [[:print:]]{-}[\\\n\"]+

%%
           
{ws}                					;

{comment_begin}               BEGIN(X);
<X>{comment_body}             ;                 
<X>{comment_bodyStars}      	;                    
<X>\n                  				;                   
<X><<EOF>>             				return yy_error(E_EOF_COMMENT);
<X>{comment_end}             	BEGIN(0);            

{num}             					 	return yy_integer_from_cstring(yytext);

\'[[:print:]]{-}[\\\n\']\' 	  return yy_integer_from_char(yytext[1]);
\'\'                					return yy_error(E_BAD_LITERAL_CHAR);
\'\\a\'           						return yy_integer_from_char('\a');
\'\\b\'           						return yy_integer_from_char('\b');
\'\\f\'           						return yy_integer_from_char('\f');
\'\\n\'           						return yy_integer_from_char('\n');
\'\\r\'           						return yy_integer_from_char('\r');
\'\\t\'           						return yy_integer_from_char('\t');
\'\\v\'           						return yy_integer_from_char('\v');
\'\\\?\'           						return yy_integer_from_char('\?');
\'\\\'\'           						return yy_integer_from_char('\'');
\'\\\"\'          						return yy_integer_from_char('\"'); 
\'\\\\\'          						return yy_integer_from_char('\\');
\'{octal_literal}\' 					return yy_integer_from_octal_char(yytext); 
\'{bad_octal_literal}\'       return yy_error(E_BAD_OCTAL_LITERAL);


\'                						BEGIN(BAD_CHAR);
<BAD_CHAR>[^\n\']+           	return yy_error(E_BAD_LITERAL_CHAR);
<BAD_CHAR>\n                 	return yy_error(E_UNTERM_CHAR);
<BAD_CHAR><<EOF>>            	return yy_error(E_EOF_CHAR);
<BAD_CHAR>"'"                	BEGIN(0);

\"                						if (yy_begin_string()) return E_OUT_OF_MEMORY;
<S>\\\n              				  ; /* continuation */                
<S>\\                				  return yy_error(E_BAD_CHAR_ESCAPE);
<S>\\a               				  if (add_char('\a')) return yy_error(E_OUT_OF_MEMORY);
<S>\\b               				  if (add_char('\b')) return yy_error(E_OUT_OF_MEMORY);
<S>\\f               				  if (add_char('\f')) return yy_error(E_OUT_OF_MEMORY);
<S>\\n               				  if (add_char('\n')) return yy_error(E_OUT_OF_MEMORY);
<S>\\t               				  if (add_char('\t')) return yy_error(E_OUT_OF_MEMORY);
<S>\\r               				  if (add_char('\r')) return yy_error(E_OUT_OF_MEMORY);
<S>\\v               				  if (add_char('\v')) return yy_error(E_OUT_OF_MEMORY);
<S>\\\?               				if (add_char('\?')) return yy_error(E_OUT_OF_MEMORY);
<S>\\\'              				  if (add_char('\'')) return yy_error(E_OUT_OF_MEMORY);
<S>\\\"              				  if (add_char('\"')) return yy_error(E_OUT_OF_MEMORY);
<S>\\\\              				  if (add_char('\\')) return yy_error(E_OUT_OF_MEMORY);                                                              
<S>{octal_literal}      		  if (add_octal_char(yytext)) return yy_error(E_OUT_OF_MEMORY);
<S>{bad_octal_literal} 				return yy_error(E_BAD_OCTAL_LITERAL);
<S>\n                  				return yy_error(E_UNTERM_STR);
<S><<EOF>>             				return yy_error(E_EOF_STR);
<S>{string_char}  						if (add_cstring(yytext, yyleng)) return yy_error(E_OUT_OF_MEMORY);
<S>\"													return yy_end_string();
                   
break              						return yy_token(BREAK);
char                					return yy_token(CHAR);
continue            					return yy_token(CONTINUE);  
do                  					return yy_token(DO);
else                					return yy_token(ELSE);
for                 					return yy_token(FOR);
goto                					return yy_token(GOTO);
if                  					return yy_token(IF);
int                 					return yy_token(INT);
long                					return yy_token(LONG);
return              					return yy_token(RETURN);
short               					return yy_token(SHORT);
signed              					return yy_token(SIGNED);
unsigned            					return yy_token(UNSIGNED);
void                					return yy_token(VOID);
while               					return yy_token(WHILE);

{id}              						return yy_id(yytext, yyleng); 

"*"                 					return yy_token(ASTERISK);                
":"                 					return yy_token(COLON);                   
"-"                 					return yy_token(DASH);                    
"+"                 					return yy_token(PLUS);                    
"?"                 					return yy_token(QUESTION_MARK);           
"="                 					return yy_token(ASSIGN);                  
"&="                					return yy_token(ASSIGN_BITWISE_AND);
"|="                					return yy_token(ASSIGN_BITWISE_OR);     
"^="                					return yy_token(ASSIGN_BITWISE_XOR);      
"<<="               					return yy_token(ASSIGN_LEFT_SHIFT);     
">>="               					return yy_token(ASSIGN_RIGHT_SHIFT);      
"+="                					return yy_token(ASSIGN_SUM);     
"-="                					return yy_token(ASSIGN_DIFFERENCE);
"*="                					return yy_token(ASSIGN_PRODUCT);      
"/="                					return yy_token(ASSIGN_QUOTIENT);         
"%="                					return yy_token(ASSIGN_REMAINDER);        
"&"                 					return yy_token(BITWISE_AND);       
"|"                 					return yy_token(BITWISE_OR);              
"^"                 					return yy_token(BITWISE_XOR);             
"~"                 					return yy_token(BITWISE_NEGATION);        
"<<"                					return yy_token(LEFT_SHIFT);              
">>"                					return yy_token(RIGHT_SHIFT);             
"/"                 					return yy_token(DIVISION);                
"%"                 					return yy_token(REMAINDER);               
"++"                					return yy_token(INCREMENT);              
"--"                					return yy_token(DECREMENT);               
"<"                 					return yy_token(LESS);                
"<="                					return yy_token(LESS_OR_EQUAL);       
">"                 					return yy_token(GREATER);             
">="                					return yy_token(GREATER_OR_EQUAL);    
"=="                					return yy_token(EQUAL_TO);            
"!="                					return yy_token(NOT_EQUAL);           
"&&"                					return yy_token(LOGICAL_AND);             
"||"                					return yy_token(LOGICAL_OR);             
"!"                 					return yy_token(LOGICAL_NEGATION);        
"("                 					return yy_token(LEFT_PAREN);              
")"                 					return yy_token(RIGHT_PAREN);             
"["                 					return yy_token(LEFT_BRACKET);            
"]"                 					return yy_token(RIGHT_BRACKET);           
"{"                 					return yy_token(LEFT_BRACE);              
"}"                 					return yy_token(RIGHT_BRACE);             
";"                 					return yy_token(STATEMENT_TERMINATOR);   
","                 					return yy_token(SEQUENTIAL_EVAL);  

.                   					return yy_error(E_NO_MATCHING_TOKEN);

%%
	int yy_token(const int token_value)               { yylval = 0; return token_value; }
	
	int yy_integer_from_char(const char value)        { yylval = (YYSTYPE)integer_from_char(value);       return LITERAL_NUMBER; }
	int yy_integer_from_cstring(const char* value)    { yylval = (YYSTYPE)integer_from_cstring(value);    return LITERAL_NUMBER; }
	int yy_integer_from_octal_char(const char* value) { yylval = (YYSTYPE)integer_from_octal_char(value); return LITERAL_NUMBER; }

	int yy_begin_string() { BEGIN(S); return initialize_string_buffer(); }
	int yy_end_string()   { BEGIN(0); yylval = (YYSTYPE)string_from_buffer(); return LITERAL_STRING; }
	
	int yy_id(const char* string, const int length)
	{
		char* newString;

		newString = (char *) malloc(sizeof(char) * (length + 1));

		if (newString)
		{
			strcpy(newString, string);
		}
		
		yylval = (YYSTYPE)newString;
		return IDENTIFIER;
	}
	
	int yy_error(int errorCode)
	{
		yylval = (YYSTYPE)errorCode;
		yyerror(decode(errorCode));
		return -1;
	}
	
	void yyerror(const char* errorMessage)
	{
		fprintf(stderr, "[ERROR] line %i: %s", yylineno, errorMessage);
	}