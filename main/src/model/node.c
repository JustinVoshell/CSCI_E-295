#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "model/node.h"

extern int yylineno;

struct node *node_basic(enum node_type type)
{
	struct node *new_node = malloc(sizeof(struct node));
	assert(new_node);
	
	new_node->node_type = type;
	new_node->line_number = yylineno;
	return new_node;
}
                       
struct node *node_int(enum node_type node_type, int value)
{
	struct node *new_node = node_basic(node_type);
	new_node->data.int_value = value;
	return new_node;
}
      
struct node *node_cstring(enum node_type node_type, const char* cstring)
{
	struct node *new_node = node_basic(node_type);
	new_node->data.cstring_value = cstring;  
	return new_node;
}

struct node *node_unary(enum node_type node_type, struct node *child)
{
	struct node *new_node = node_basic(node_type);
	new_node->data.children = &child;
	return new_node;
}

struct node *node_binary(enum node_type node_type, struct node *left_child, struct node *right_child)
{
	struct node *new_node = node_basic(node_type);
	new_node->data.children = (struct node **) malloc(2 * sizeof(struct node *));
	new_node->data.children[0] = left_child;
	new_node->data.children[1] = right_child;  
	return new_node;
}    

struct node *node_literal_integer(enum node_type node_type, struct integer_data *integer_data)
{
	struct node *new_node = node_basic(node_type);
	new_node->data.integer_data = integer_data;
	return new_node;
}

struct node *node_literal_string(enum node_type node_type, struct string_data *string_data)
{
	struct node *new_node = node_basic(node_type);
	new_node->data.string_data = string_data;
	return new_node;
}

struct node *node_error(enum error_type error_type)
{
	struct node *new_node = node_basic(error_type);
	new_node->data.error_type = error_type;
	return new_node;
}