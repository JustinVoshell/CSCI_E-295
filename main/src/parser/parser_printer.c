#include <stdio.h>

#include "model/node.h"
#include "parser/parser_printer.h"

extern FILE* output_file;

void pp_print_translation_unit_(struct node *translation_unit)
{
	struct node *next_translation_unit = translation_unit->data.children[0];
	if (next_translation_unit) pp_print(next_translation_unit);
	pp_print(translation_unit->data.children[1]);
}
	      
void pp_print_top_level_declaration_(struct node *declaration)
{
	pp_print(declaration->data.children[0]);
}
	 
void pp_print_declaration_(struct node *declaration)
{
	pp_print(declaration->data.children[0]);
	fputs(" ", output_file);
	pp_print(declaration->data.children[1]);
	fputs(";", output_file);
}
	           
void pp_print_declaration_specifiers_(struct node *declaration_specifiers)
{
	pp_print(declaration_specifiers->data.children[0]);
}

void pp_print_type_specifier_(struct node *type_specifier)
{
	pp_print(type_specifier->data.children[0]);
}

void pp_print_void_type_specifier_(void)
{
	fputs("void", output_file);
}
       
void pp_print_integer_type_specifier_(struct node* integer_type_specifier)
{
	pp_print(integer_type_specifier->data.children[0]);
}

void pp_print_signed_type_specifier_(struct node* signed_type_specifier)
{
	switch(signed_type_specifier->data.integer_data->type)
	{
		case INTEGER_DATA_SIGNED_CHAR  : { fputs("signed char",      output_file); break; }
		case INTEGER_DATA_SIGNED_SHORT : { fputs("signed short int", output_file); break; }
		case INTEGER_DATA_SIGNED_INT   : { fputs("signed int",       output_file); break; }
		case INTEGER_DATA_SIGNED_LONG  : { fputs("signed long int",  output_file); break; }
		default: break;
	}
}
                                                                                       
void pp_print_unsigned_type_specifier_(struct node* unsigned_type_specifier)
{                                                                                                                                
	switch(unsigned_type_specifier->data.integer_data->type)                                                                                                
	{                                                                                                                              
		case INTEGER_DATA_UNSIGNED_CHAR  : { fputs("unsigned char",      output_file); break; }                                            
		case INTEGER_DATA_UNSIGNED_SHORT : { fputs("unsigned short int", output_file); break; }                                            
		case INTEGER_DATA_UNSIGNED_INT   : { fputs("unsigned int",       output_file); break; }                                            
		case INTEGER_DATA_UNSIGNED_LONG  : { fputs("unsigned long int",  output_file); break; }                                            
		default: break;
	}
}
   	        	   
void pp_print_ideclarator_list_(struct node *ideclarator_list)
{
	if (ideclarator_list->data.children[0]) pp_print(ideclarator_list->data.children[0]);
	pp_print(ideclarator_list->data.children[1]);
}
	      
void pp_print_ideclarator_(struct node *ideclarator)
{
	pp_print(ideclarator->data.children[0]);
}
	           
void pp_print_declarator_(struct node *declarator)
{
	pp_print(declarator->data.children[0]);
}

void pp_print_pointer_to_declarator_(struct node *pointer, struct node *direct_declarator)
{
	fputs("(*", output_file);
	
	if (pointer->data.children[0])
		pp_print_pointer_to_declarator_(pointer, direct_declarator);
	
	else
		pp_print(direct_declarator);
		
	fputs(")", output_file);
}	    
	            
void pp_print_pointer_declarator_(struct node *pointer_declarator)
{
	pp_print_pointer_to_declarator_(pointer_declarator->data.children[0], pointer_declarator->data.children[1]);
}
	               
void pp_print_direct_declarator_(struct node *direct_declarator)
{
	pp_print(direct_declarator);
}
	     
void pp_print_simple_declarator_(struct node *simple_declarator)
{
	pp_print(simple_declarator);
}
          
void pp_print_identifier_(struct node *identifier)
{
	fputs(identifier->data.cstring_value, output_file);
} 
                                                                                                                                                
/*       
void pp_print_literal_string_(struct node *literal_string)
{

}

void pp_print_literal_integer_(struct node *literal_integer)
{ 
	
}
*/

void pp_print(struct node *node)                                                                     
{                                                                                                    
	switch(node->node_type)                                                                            
	{                                                                                                  
		case NODE_TRANSLATION_UNIT       : { pp_print_translation_unit_(node);       break; }                                                                                             
		case NODE_TOP_LEVEL_DECLARATION  : { pp_print_top_level_declaration_(node);  break; }                                                                                                  
		case NODE_DECLARATION            : { pp_print_declaration_(node);            break; }                                                                                                            
		case NODE_DECLARATION_SPECIFIERS : { pp_print_declaration_specifiers_(node); break; }                                                                                                 
		case NODE_TYPE_SPECIFIER         : { pp_print_type_specifier_(node);         break; }                                                                                                         
		case NODE_INTEGER_TYPE_SPECIFIER : { pp_print_integer_type_specifier_(node); break; }                                                                                                 
		case NODE_VOID_TYPE_SPECIFIER    : { pp_print_void_type_specifier_();        break; }                                                                                                    
		case NODE_IDECL_LIST             : { pp_print_ideclarator_list_(node);       break; }                                                                                                             
		case NODE_IDECLARATOR            : { pp_print_ideclarator_(node);            break; }                                                                                                            
		case NODE_DECLARATOR             : { pp_print_declarator_(node);             break; }
		case NODE_POINTER_DECLARATOR     : { pp_print_pointer_declarator_(node);     break; }
/*
		case NODE_POINTER                : { pp_print_pointer_(node);                break; }
*/
		case NODE_DIRECT_DECLARATOR      : { pp_print_direct_declarator_(node);      break; }
		case NODE_SIMPLE_DECLARATOR      : { pp_print_simple_declarator_(node);      break; } 
		case NODE_IDENTIFIER             : { pp_print_identifier_(node);             break; }  
/*      
		case NODE_LITERAL_STRING         : { pp_print_literal_string(node);          break; }
		case NODE_LITERAL_INTEGER        : { pp_print_literal_integer(node);         break; }
		case NODE_ERROR                  : { pp_print_node_error(node);              break; }
*/      
		  
		default : break;
	}
}