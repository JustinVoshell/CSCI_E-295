%{
	#include <stdio.h>
  #include "model/resource.h"
	#include "model/node.h"
	#define YYSTYPE struct node*

	int yylex();
	void yyerror(const char*);	
	extern struct node *root_node; 

  int is_function_declarator(struct node* declarator);
%}

%debug
%verbose
%error_verbose
%locations

%token IDENTIFIER
%token LITERAL_STRING      
%token LITERAL_NUMBER      
%token BREAK               
%token CHAR                
%token CONTINUE            
%token DO                  
%token ELSE                
%token FOR                 
%token GOTO                
%token IF                  
%token INT                 
%token LONG                
%token RETURN              
%token SHORT               
%token SIGNED              
%token UNSIGNED            
%token VOID                
%token WHILE               
%token ASTERISK            
%token COLON               
%token DASH                
%token PLUS                
%token QUESTION_MARK       
%token ASSIGN              
%token ASSIGN_BITWISE_AND  
%token ASSIGN_BITWISE_OR   
%token ASSIGN_BITWISE_XOR  
%token ASSIGN_LEFT_SHIFT   
%token ASSIGN_RIGHT_SHIFT  
%token ASSIGN_SUM          
%token ASSIGN_DIFFERENCE   
%token ASSIGN_PRODUCT      
%token ASSIGN_QUOTIENT     
%token ASSIGN_REMAINDER    
%token BITWISE_AND         
%token BITWISE_OR          
%token BITWISE_XOR         
%token BITWISE_NEGATION    
%token LEFT_SHIFT          
%token RIGHT_SHIFT         
%token DIVISION            
%token REMAINDER           
%token INCREMENT           
%token DECREMENT           
%token LESS                
%token LESS_OR_EQUAL                                                                                                    
%token GREATER                                                                                                          
%token GREATER_OR_EQUAL                                                                                                 
%token EQUAL_TO                                                                                                         
%token NOT_EQUAL                                                                                                        
%token LOGICAL_AND                                                                                                      
%token LOGICAL_OR                                                                                                       
%token LOGICAL_NEGATION                                                                                                 
%token LEFT_PAREN                                                                                                       
%token RIGHT_PAREN                                                                                                      
%token LEFT_BRACKET                                                                                                     
%token RIGHT_BRACKET                                                                                                    
%token LEFT_BRACE                                                                                                       
%token RIGHT_BRACE                                                                                                      
%token SEMICOLON
%token SEQUENTIAL_EVAL 
%token SCANNER_ERROR    

%start root

%%

root                                   : translation_unit                                                              { root_node = node_unary(NODE_ROOT, $1);             }
                                       ;

abstract_declarator                    : pointer                                                                       { $$ = node_binary(NODE_ABSTRACT_DECLARATOR, $1,  0); }
                                       | direct_abstract_declarator                                                    { $$ = node_binary(NODE_ABSTRACT_DECLARATOR,  0, $1); }        
                                       | pointer direct_abstract_declarator                                            { $$ = node_binary(NODE_ABSTRACT_DECLARATOR, $1, $2); }
                                       ;

array_declarator                       : direct_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET              { $$ = node_binary(NODE_ARRAY_DECLARATOR, $1, $3); }
                                       | direct_declarator LEFT_BRACKET RIGHT_BRACKET                                  { $$ = node_binary(NODE_ARRAY_DECLARATOR, $1,  0); }
                                       ;

constant_expression                    : LITERAL_NUMBER                                                                { $$ = node_unary(NODE_CONSTANT_EXPRESSION, $1);   }
                                       ;
             
declaration                            : type_specifier declarator_list SEMICOLON                                      { $$ = node_binary(NODE_DECLARATION, $1, $2);        }
                                       | error SEMICOLON
                                       ;

declarator                             : pointer_declarator                                                            { $$ = $1 }
	                                     | direct_declarator                                                             { $$ = $1 }
                                       ;

declarator_list                        : declarator                                                                    { $$ = node_binary(NODE_DECLARATOR_LIST,  0, $1);  }
                                       | declarator_list SEQUENTIAL_EVAL declarator                                    { $$ = node_binary(NODE_DECLARATOR_LIST, $1, $3);  }
                                       ;

direct_abstract_declarator             : LEFT_PAREN abstract_declarator RIGHT_PAREN                                    { $$ = $2 }
                                       | LEFT_BRACKET constant_expression RIGHT_BRACKET                                { $$ = node_binary(NODE_DIRECT_ABSTRACT_DECLARATOR,  0, $2); }
                                       | direct_abstract_declarator LEFT_BRACKET constant_expression RIGHT_BRACKET     { $$ = node_binary(NODE_DIRECT_ABSTRACT_DECLARATOR, $1, $3); }
                                       | direct_abstract_declarator LEFT_BRACKET RIGHT_BRACKET                         { $$ = node_binary(NODE_DIRECT_ABSTRACT_DECLARATOR, $1,  0); }
                                       ;                                                                             

direct_declarator                      : simple_declarator                                                             { $$ = $1 }
	                                     | LEFT_PAREN declarator RIGHT_PAREN                                             { $$ = $2 }
                                       | function_declarator                                                           { $$ = $1 }
                                       | array_declarator                                                              { $$ = $1 }
                                       ;

function_declarator                    : direct_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN                  { $$ = node_binary(NODE_FUNCTION_DECLARATOR, $1, $3); }
                                       ;

integer_type_specifier                 : signed_type_specifier                                                         { $$ = $1 }
                                       | unsigned_type_specifier                                                       { $$ = $1 }
                                       ;

parameter_declaration                  : type_specifier declarator                                                     { if (node_is_function_declarator($2))
                                                                                                                         { 
                                                                                                                           yyerror(resource(ERROR_FUNCTION_AS_FUNCTION_PARAMETER));
                                                                                                                           YYERROR;
                                                                                                                         }
                                                                                                                         else $$ = node_binary(NODE_PARAMETER_DECLARATION, $1, $2);
                                                                                                                       }
                                       | type_specifier                                                                { $$ = node_binary(NODE_PARAMETER_DECLARATION, $1,  0); }
                                       | type_specifier abstract_declarator                                            { $$ = node_binary(NODE_PARAMETER_DECLARATION, $1, $2); }
                                       ;

parameter_list                         : parameter_declaration                                                         { $$ = node_binary(NODE_PARAMETER_LIST,  0, $1); }
                                       | parameter_list SEQUENTIAL_EVAL parameter_declaration                          { $$ = node_binary(NODE_PARAMETER_LIST, $1, $3); }
                                       ;

parameter_type_list                    : parameter_list                                                                { $$ = node_unary(NODE_PARAMETER_TYPE_LIST, $1); }
                                       ;

pointer                                : ASTERISK                                                                      { $$ = node_unary(NODE_POINTER, 0 ); }
	                                     | ASTERISK pointer                                                              { $$ = node_unary(NODE_POINTER, $2); }
                                       ;	

pointer_declarator                     : pointer direct_declarator                                                     { $$ = node_pointer_declarator($1, $2); }
                                       ;	

signed_type_specifier                  : CHAR                                                                          { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_CHAR);   }
                                       | SIGNED CHAR                                                                   { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_CHAR);   }
                                       | SHORT                                                                         { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_SHORT);  }
                                       | SHORT INT                                                                     { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_SHORT);  }
                                       | SIGNED SHORT                                                                  { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_SHORT);  }
                                       | SIGNED SHORT INT                                                              { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_SHORT);  }
                                       | INT                                                                           { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_INT);    }
                                       | SIGNED                                                                        { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_INT);    }
                                       | SIGNED INT                                                                    { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_INT);    }
                                       | LONG                                                                          { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_LONG);   }
                                       | LONG INT                                                                      { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_LONG);   }
                                       | SIGNED LONG                                                                   { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_LONG);   }
                                       | SIGNED LONG INT                                                               { $$ = node_int(NODE_SIGNED_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_LONG);   }
                                       ;

simple_declarator                      : IDENTIFIER                                                                    { $$ = node_unary(NODE_SIMPLE_DECLARATOR, $1); }
                                       ;

top_level_declaration                  : declaration                                                                   { $$ = node_unary(NODE_TOP_LEVEL_DECLARATION, $1);   }
                                     /*| function_definition */
                                       ;

translation_unit                       : top_level_declaration                                                         { $$ = node_binary(NODE_TRANSLATION_UNIT,  0, $1);   }
                                       | translation_unit top_level_declaration                                        { $$ = node_binary(NODE_TRANSLATION_UNIT, $1, $2);   }
                                       | error
                                       ;

type_specifier                         : integer_type_specifier                                                        { $$ = $1 }
                                       | void_type_specifier                                                           { $$ = $1 }
                                       ;

unsigned_type_specifier                : UNSIGNED CHAR                                                                 { $$ = node_int(NODE_UNSIGNED_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_CHAR); }
	                                     | UNSIGNED SHORT                                                                { $$ = node_int(NODE_UNSIGNED_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_SHORT);}
	                                     | UNSIGNED SHORT INT                                                            { $$ = node_int(NODE_UNSIGNED_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_SHORT);}
	                                     | UNSIGNED                                                                      { $$ = node_int(NODE_UNSIGNED_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_INT);  }
	                                     | UNSIGNED INT                                                                  { $$ = node_int(NODE_UNSIGNED_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_INT);  }
	                                     | UNSIGNED LONG                                                                 { $$ = node_int(NODE_UNSIGNED_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_LONG); }
	                                     | UNSIGNED LONG INT                                                             { $$ = node_int(NODE_UNSIGNED_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_LONG); }
                                       ;                                                                               

void_type_specifier                    : VOID                                                                          { $$ = node_basic(NODE_VOID_TYPE_SPECIFIER);  }
                                       ;

%%