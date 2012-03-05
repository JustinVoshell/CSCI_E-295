#include <stdio.h>
#include "model/node.h"
#include "model/resource.h"

extern FILE* output_file;

int tabDepth = 0;

int debug_print(struct node *node)
{ 
	int idxTabDepth;
	
	fputs("\n", output_file);	  
	for (idxTabDepth = 0; idxTabDepth < tabDepth; idxTabDepth++)
	{
		fputs("\t", output_file);
	}
	
	if (!node) { fputs("NULL", output_file); return 1; }
 
  switch (node->node_type)
  {
		case NODE_ROOT:
			fputs("NODE_ROOT", output_file); 
			tabDepth++;
			debug_print(node->data.child);
			tabDepth--;
			break;
			
		case NODE_TRANSLATION_UNIT:
			fputs("NODE_TRANSLATION_UNIT", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]);
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		case NODE_TOP_LEVEL_DECLARATION:
			fputs("NODE_TOP_LEVEL_DECLARATION", output_file); 
			tabDepth++;
			debug_print(node->data.child);
			tabDepth--;
			break;
			
		case NODE_DECLARATION:
			fputs("NODE_DECLARATION", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]);
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		case NODE_SIGNED_TYPE_SPECIFIER:
			fputs("NODE_SIGNED_TYPE_SPECIFIER: ", output_file); 
			fputs(resource(node->data.int_value), output_file);
			break;
			
		case NODE_UNSIGNED_TYPE_SPECIFIER:
			fputs("NODE_UNSIGNED_TYPE_SPECIFIER :", output_file); 
			fputs(resource(node->data.int_value), output_file);
			break;
			
		case NODE_VOID_TYPE_SPECIFIER:
			fputs("NODE_VOID_TYPE_SPECIFIER", output_file); 
			break;
			
		case NODE_DECLARATOR_LIST:
			fputs("NODE_DECLARATOR_LIST", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]); 
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		case NODE_POINTER_DECLARATOR:
			fputs("NODE_POINTER_DECLARATOR", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]);
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		case NODE_POINTER:
			fputs("NODE_POINTER", output_file); 
			tabDepth++;
			debug_print(node->data.child);
			tabDepth--;
			break;
			
		case NODE_SIMPLE_DECLARATOR:
			fputs("NODE_SIMPLE_DECLARATOR", output_file); 
			tabDepth++;
			debug_print(node->data.child);
			tabDepth--; 
			break;
			
		case NODE_IDENTIFIER:
			fputs("NODE_IDENTIFIER: ", output_file); 
			fputs(node->data.cstring_value, output_file);
			break;
				
		case NODE_LITERAL_STRING:
			fputs("NODE_LITERAL_STRING: ", output_file); 
			fputs(node->data.string_data->buffer, output_file);
			break;
			
		case NODE_LITERAL_INTEGER:
			fputs("NODE_LITERAL_INTEGER: ", output_file); 
			fprintf(output_file, "%lu", node->data.integer_data->value);
			break;
			
		case NODE_ERROR:
			fputs("NODE_ERROR: ", output_file); 
			fputs(resource(node->data.error_type), output_file);
			break;
			
		case NODE_ARRAY_DECLARATOR:
			fputs("NODE_ARRAY_DECLARATOR", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]); 
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		case NODE_CONSTANT_EXPRESSION:
			fputs("NODE_CONSTANT_EXPRESSION", output_file); 
			tabDepth++;
			debug_print(node->data.child);
			tabDepth--;
			break;
			
		case NODE_FUNCTION_DECLARATOR:
			fputs("NODE_FUNCTION_DECLARATOR", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]);
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		case NODE_PARAMETER_TYPE_LIST:
			fputs("NODE_PARAMETER_TYPE_LIST", output_file); 
			tabDepth++;
			debug_print(node->data.child);
			tabDepth--;
			break;
			
		case NODE_PARAMETER_LIST:
			fputs("NODE_PARAMETER_LIST", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]);
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		case NODE_PARAMETER_DECLARATION:
			fputs("NODE_PARAMETER_DECLARATION", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]); 
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		case NODE_ABSTRACT_DECLARATOR:
			fputs("NODE_ABSTRACT_DECLARATOR", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]);
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		case NODE_DIRECT_ABSTRACT_DECLARATOR:
			fputs("NODE_DIRECT_ABSTRACT_DECLARATOR", output_file); 
			tabDepth++;
			debug_print(node->data.children[0]);
			debug_print(node->data.children[1]);
			tabDepth--;
			break;
			
		default: 
			fprintf(output_file, "UNKNOWN NODE %i", node->node_type);
			return 1;
			break;
  }
	return 0;
}