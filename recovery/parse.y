%{
  #include <stdio.h>
  #include "node.h"
	
  #define YYSTYPE struct node*
	
  int yylex();
  void yyerror(const char*);
	
  extern struct node *root_node; 
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

root : declaration_list { root_node = $1 }
;

declaration : type_specifier declarator_list SEMICOLON { $$ = node_declaration($1, $2); }
;

declaration_list : declaration                  { $$ = node_declaration_list( 0, $1);  }
                 | declaration_list declaration { $$ = node_declaration_list($1, $2); } 
;

declarator : pointer direct_declarator { $$ = node_declarator($1, $2); }
           | direct_declarator         { $$ = node_declarator( 0, $1); }
;

declarator_list : declarator                                 { $$ = node_declarator_list( 0, $1); }
		| declarator_list SEQUENTIAL_EVAL declarator { $$ = node_declarator_list($1, $3); }
;

direct_declarator : IDENTIFIER                        { $$ = $1 }
                  | LEFT_PAREN declarator RIGHT_PAREN { $$ = $2 }
;

pointer : ASTERISK          { $$ = node_pointer( 0)  }
        | pointer ASTERISK  { $$ = node_pointer($1); }
;

type_specifier : VOID               { $$ = node_type_specifier(INTEGER_TYPE_VOID);           }
               | CHAR               { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_CHAR);    }
               | SIGNED CHAR        { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_CHAR);    }
               | UNSIGNED CHAR      { $$ = node_type_specifier(INTEGER_TYPE_UNSIGNED_CHAR);  }
	       | SHORT              { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_SHORT);   }
	       | SIGNED SHORT       { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_SHORT);   }
	       | SHORT INT          { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_SHORT);   }
	       | SIGNED SHORT INT   { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_SHORT);   }
	       | UNSIGNED SHORT     { $$ = node_type_specifier(INTEGER_TYPE_UNSIGNED_SHORT); }
               | UNSIGNED SHORT INT { $$ = node_type_specifier(INTEGER_TYPE_UNSIGNED_SHORT); }
	       | SIGNED             { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_INT);     }
	       | INT                { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_INT);     }
	       | SIGNED INT         { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_INT);     }
	       | UNSIGNED           { $$ = node_type_specifier(INTEGER_TYPE_UNSIGNED_INT);   }
	       | UNSIGNED INT       { $$ = node_type_specifier(INTEGER_TYPE_UNSIGNED_INT);   }
	       | LONG 		    { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_LONG);    }
	       | SIGNED LONG        { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_LONG);    }
               | LONG INT           { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_LONG);    }
	       | SIGNED LONG INT    { $$ = node_type_specifier(INTEGER_TYPE_SIGNED_LONG);    }
	       | UNSIGNED LONG      { $$ = node_type_specifier(INTEGER_TYPE_UNSIGNED_LONG);  }
	       | UNSIGNED LONG INT  { $$ = node_type_specifier(INTEGER_TYPE_UNSIGNED_LONG);  }
;

%%
