%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <errno.h>
  #include <limits.h>

	#include "model/node.h" 
  #define YYSTYPE struct node*

  #ifdef STANDALONE_SCANNER
  extern YYSTYPE yylval;
  #endif

  #include "model/tokens.h"
	#include "model/resource.h"
  #include "model/error_type.h"
  #include "model/integer_data.h"
  #include "model/string_data.h"

	int scan_integer_from_char(const char);
	int scan_integer_from_cstring(const char*);
	int scan_integer_from_octal_char(const char*);
	
	int scan_begin_string();
	int scan_end_string();
	
	int scan_id(const char *name, const int length);
	int scan_token(const int tokenValue);
	int scan_error(const enum error_type error_type);
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
<X><<EOF>>             				return scan_error(ERROR_EOF_COMMENT);
<X>{comment_end}             	BEGIN(0);            

{num}             					 	return scan_integer_from_cstring(yytext);

\'[[:print:]]{-}[\\\n\']\' 	  return scan_integer_from_char(yytext[1]);
\'\'                					return scan_error(ERROR_BAD_LITERAL_CHAR);
\'\\a\'           						return scan_integer_from_char('\a');
\'\\b\'           						return scan_integer_from_char('\b');
\'\\f\'           						return scan_integer_from_char('\f');
\'\\n\'           						return scan_integer_from_char('\n');
\'\\r\'           						return scan_integer_from_char('\r');
\'\\t\'           						return scan_integer_from_char('\t');
\'\\v\'           						return scan_integer_from_char('\v');
\'\\\?\'           						return scan_integer_from_char('\?');
\'\\\'\'           						return scan_integer_from_char('\'');
\'\\\"\'          						return scan_integer_from_char('\"'); 
\'\\\\\'          						return scan_integer_from_char('\\');
\'{octal_literal}\' 					return scan_integer_from_octal_char(yytext); 
\'{bad_octal_literal}\'       return scan_error(ERROR_BAD_OCTAL_ESCAPE);


\'                						BEGIN(BAD_CHAR);
<BAD_CHAR>[^\n\']+           	return scan_error(ERROR_BAD_LITERAL_CHAR);
<BAD_CHAR>\n                 	return scan_error(ERROR_UNTERM_CHAR);
<BAD_CHAR><<EOF>>            	return scan_error(ERROR_EOF_CHAR);
<BAD_CHAR>"'"                	BEGIN(0);

\"                						if (scan_begin_string()) return ERROR_OUT_OF_MEMORY;
<S>\\\n              				  ; /* continuation */                
<S>\\                				  return scan_error(ERROR_BAD_CHAR_ESCAPE);
<S>\\a               				  if (string_data_add_char('\a')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\b               				  if (string_data_add_char('\b')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\f               				  if (string_data_add_char('\f')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\n               				  if (string_data_add_char('\n')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\t               				  if (string_data_add_char('\t')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\r               				  if (string_data_add_char('\r')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\v               				  if (string_data_add_char('\v')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\\?               				if (string_data_add_char('\?')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\\'              				  if (string_data_add_char('\'')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\\"              				  if (string_data_add_char('\"')) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\\\\              				  if (string_data_add_char('\\')) return scan_error(ERROR_OUT_OF_MEMORY);                                                              
<S>{octal_literal}      		  if (string_data_add_octal_char(yytext)) return scan_error(ERROR_OUT_OF_MEMORY);
<S>{bad_octal_literal} 				return scan_error(ERROR_BAD_OCTAL_ESCAPE);
<S>\n                  				return scan_error(ERROR_UNTERM_STR);
<S><<EOF>>             				return scan_error(ERROR_EOF_STR);
<S>{string_char}  						if (string_data_add_cstring(yytext, yyleng)) return scan_error(ERROR_OUT_OF_MEMORY);
<S>\"													return scan_end_string();
                   
break              						return scan_token(BREAK);
char                					return scan_token(CHAR);
continue            					return scan_token(CONTINUE);  
do                  					return scan_token(DO);
else                					return scan_token(ELSE);
for                 					return scan_token(FOR);
goto                					return scan_token(GOTO);
if                  					return scan_token(IF);
int                 					return scan_token(INT);
long                					return scan_token(LONG);
return              					return scan_token(RETURN);
short               					return scan_token(SHORT);
signed              					return scan_token(SIGNED);
unsigned            					return scan_token(UNSIGNED);
void                					return scan_token(VOID);
while               					return scan_token(WHILE);

{id}              						return scan_id(yytext, yyleng); 

"*"                 					return scan_token(ASTERISK);                
":"                 					return scan_token(COLON);                   
"-"                 					return scan_token(DASH);                    
"+"                 					return scan_token(PLUS);                    
"?"                 					return scan_token(QUESTION_MARK);           
"="                 					return scan_token(ASSIGN);                  
"&="                					return scan_token(ASSIGN_BITWISE_AND);
"|="                					return scan_token(ASSIGN_BITWISE_OR);     
"^="                					return scan_token(ASSIGN_BITWISE_XOR);      
"<<="               					return scan_token(ASSIGN_LEFT_SHIFT);     
">>="               					return scan_token(ASSIGN_RIGHT_SHIFT);      
"+="                					return scan_token(ASSIGN_SUM);     
"-="                					return scan_token(ASSIGN_DIFFERENCE);
"*="                					return scan_token(ASSIGN_PRODUCT);      
"/="                					return scan_token(ASSIGN_QUOTIENT);         
"%="                					return scan_token(ASSIGN_REMAINDER);        
"&"                 					return scan_token(BITWISE_AND);       
"|"                 					return scan_token(BITWISE_OR);              
"^"                 					return scan_token(BITWISE_XOR);             
"~"                 					return scan_token(BITWISE_NEGATION);        
"<<"                					return scan_token(LEFT_SHIFT);              
">>"                					return scan_token(RIGHT_SHIFT);             
"/"                 					return scan_token(DIVISION);                
"%"                 					return scan_token(REMAINDER);               
"++"                					return scan_token(INCREMENT);              
"--"                					return scan_token(DECREMENT);               
"<"                 					return scan_token(LESS);                
"<="                					return scan_token(LESS_OR_EQUAL);       
">"                 					return scan_token(GREATER);             
">="                					return scan_token(GREATER_OR_EQUAL);    
"=="                					return scan_token(EQUAL_TO);            
"!="                					return scan_token(NOT_EQUAL);           
"&&"                					return scan_token(LOGICAL_AND);             
"||"                					return scan_token(LOGICAL_OR);             
"!"                 					return scan_token(LOGICAL_NEGATION);        
"("                 					return scan_token(LEFT_PAREN);              
")"                 					return scan_token(RIGHT_PAREN);             
"["                 					return scan_token(LEFT_BRACKET);            
"]"                 					return scan_token(RIGHT_BRACKET);           
"{"                 					return scan_token(LEFT_BRACE);              
"}"                 					return scan_token(RIGHT_BRACE);             
";"                 					return scan_token(SEMICOLON);   
","                 					return scan_token(SEQUENTIAL_EVAL);  

.                   					return scan_error(ERROR_NO_MATCHING_TOKEN);

%%
	int scan_token(const int token_value)
	{ 
		yylval = 0;
		return token_value;
	}

	int scan_integer_from_char(const char value)
	{ 
		yylval = node_literal_integer(NODE_LITERAL_INTEGER, integer_data_from_char(value));
		return LITERAL_NUMBER;
	}

	int scan_integer_from_cstring(const char* value)    
	{ 
		yylval = node_literal_integer(NODE_LITERAL_INTEGER, integer_data_from_cstring(value));
		return LITERAL_NUMBER;
	}

	int scan_integer_from_octal_char(const char* value) 
	{ 
		yylval = node_literal_integer(NODE_LITERAL_INTEGER, integer_data_from_octal_char(value)); 
		return LITERAL_NUMBER;
	}

	int scan_begin_string() 
	{ 
		BEGIN(S);
		return string_data_new_buffer();
	}

	int scan_end_string()   
	{ 
		BEGIN(0);
		yylval = node_literal_string(NODE_LITERAL_STRING, string_data_from_buffer()); 
		return LITERAL_STRING;
	}

	int scan_id(const char* string, const int length)
	{
		char* name = (char *) malloc(sizeof(char) * (length + 1));
		if (name) strcpy(name, string);
	
		yylval = node_cstring(NODE_IDENTIFIER, name);
		return IDENTIFIER;
	}

	int scan_error(enum error_type error_type)
	{
		yylval = node_error(error_type);
		return SCANNER_ERROR;
	}
