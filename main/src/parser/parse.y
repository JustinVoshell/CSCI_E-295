%{
	#include <stdio.h>
	#include "model/node.h"
	#define YYSTYPE struct node*

	void yyerror(const char*);	
	extern struct node *root_node; 

	int yylex();
%}

%debug
%verbose
%error_verbose

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

root                                   : translation_unit                                                              { root_node = $1; }
                                       ;

translation_unit                       : top_level_declaration                                                         { $$ = node_binary(NODE_TRANSLATION_UNIT,  0, $1);   }
                                       | translation_unit top_level_declaration                                        { $$ = node_binary(NODE_TRANSLATION_UNIT, $1, $2);   }
                                       ;

top_level_declaration                  : declaration                                                                   { $$ = node_unary(NODE_TOP_LEVEL_DECLARATION, $1);   }
                                     /*| function_definition */
                                       ;

declaration                            : declaration_specifiers initialized_declarator_list SEMICOLON                  { $$ = node_binary(NODE_DECLARATION, $1, $2);        }
                                       ;

declaration_specifiers                 : type_specifier                                                                { $$ = node_unary(NODE_DECLARATION_SPECIFIERS, $1);  }
                                       ;
	
type_specifier                         : integer_type_specifier                                                        { $$ = node_unary(NODE_TYPE_SPECIFIER, $1);          }
                                       | void_type_specifier                                                           { $$ = node_unary(NODE_TYPE_SPECIFIER, $1);          }
                                       ;

integer_type_specifier								 : signed_type_specifier                                                         { $$ = node_unary(NODE_SIGNED_TYPE_SPECIFIER, $1);   }
																			 | unsigned_type_specifier                                                       { $$ = node_unary(NODE_UNSIGNED_TYPE_SPECIFIER, $1); }
																			 ;

signed_type_specifier                  : CHAR                                                                          { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_CHAR);   }
	                                     | SIGNED CHAR                                                                   { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_CHAR);   }
	                                     | SHORT                                                                         { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_SHORT);  }
                                       | SHORT INT                                                                     { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_SHORT);  }
	                                     | SIGNED SHORT                                                                  { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_SHORT);  }
                                     	 | SIGNED SHORT INT                                                              { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_SHORT);  }
	                                     | INT                                                                           { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_INT);    }
	                                     | SIGNED                                                                        { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_INT);    }
	                                     | SIGNED INT                                                                    { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_INT);    }
	                                     | LONG 						                                                             { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_LONG);   }
	                                     | LONG INT                                                                      { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_LONG);   }
	                                     | SIGNED LONG                                                                   { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_LONG);   }
	                                     | SIGNED LONG INT                                                               { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_SIGNED_LONG);   }
                                       ;

unsigned_type_specifier                : UNSIGNED CHAR                                                                 { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_CHAR); }
	                                     | UNSIGNED SHORT                                                                { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_SHORT);}
	                                     | UNSIGNED SHORT INT                                                            { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_SHORT);}
	                                     | UNSIGNED                                                                      { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_INT);  }
	                                     | UNSIGNED INT                                                                  { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_INT);  }
	                                     | UNSIGNED LONG                                                                 { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_LONG); }
	                                     | UNSIGNED LONG INT                                                             { $$ = node_int(NODE_INTEGER_TYPE_SPECIFIER, INTEGER_DATA_UNSIGNED_LONG); }
                                       ;                                                                               

void_type_specifier                    : VOID                                                                          { $$ = node_basic(NODE_VOID_TYPE_SPECIFIER);  }
                                       ;

initialized_declarator_list            : initialized_declarator                                                        { $$ = node_binary(NODE_IDECL_LIST, 0,  $1);  }
                                       | initialized_declarator_list SEQUENTIAL_EVAL initialized_declarator            { $$ = node_binary(NODE_IDECL_LIST, $1, $2);  }
                                       ;

initialized_declarator                 : declarator                                                                    { $$ = node_unary(NODE_IDECLARATOR, $1);      }
                                       ;

declarator                             : pointer_declarator                                                            { $$ = node_unary(NODE_DECLARATOR, $1);       }
	                                     | direct_declarator                                                             { $$ = node_unary(NODE_DECLARATOR, $1);       }
                                       ;

pointer_declarator                     : pointer direct_declarator                                                     { $$ = node_binary(NODE_POINTER_DECLARATOR, $1, $2); }
                                       ;	

pointer                                : ASTERISK                                                                      { $$ = node_unary(NODE_POINTER, 0 ); }
	                                     | ASTERISK pointer                                                              { $$ = node_unary(NODE_POINTER, $1); }
                                       ;	

direct_declarator                      : simple_declarator                                                             { $$ = node_unary(NODE_DIRECT_DECLARATOR, $1); }
	                                     | LEFT_PAREN declarator RIGHT_PAREN                                             { $$ = node_unary(NODE_DIRECT_DECLARATOR, $1); }
                                     /*| function_declarator */
                                     /*| array_declarator    */
                                       ;

simple_declarator                      : IDENTIFIER                                                                    { $$ = node_unary(NODE_SIMPLE_DECLARATOR, $1); }
                                       ;

%%