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
	new_node->data.child = child;
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

int node_is(enum node_type node_type, struct node *test_node)
{
  return (test_node && test_node->node_type == node_type);
}

int node_is_function_declarator(struct node *declarator, enum node_should_dereference_pointer deref)
{
  if (!declarator) return 0;
  
  if (node_is(NODE_POINTER_DECLARATOR, declarator) && deref == NODE_DEREF_POINTER)
  {
    declarator = declarator->data.children[1];
  }
  return node_is(NODE_FUNCTION_DECLARATOR, declarator);
}

int nodes_are_function_declarators(struct node *declarator_list, enum node_should_dereference_pointer deref)
{
  while(declarator_list)
  {
    if (!node_is_function_declarator(declarator_list->data.children[1], deref)) return 0;
    declarator_list = declarator_list->data.children[0];
  }
  return 1;
}

int node_is_valid_parameter_list(struct node *list_node, struct node *parameter_declaration)
{
  if (node_is(NODE_VOID_TYPE_SPECIFIER, parameter_declaration->data.children[0])) return 0;
  if (node_is(NODE_VOID_TYPE_SPECIFIER, list_node->data.children[1]->data.children[0])) return 0;
  return 1;
}

struct node *node_pointer_declarator(struct node *pointer, struct node *declarator)
{
  if (node_is(NODE_POINTER_DECLARATOR, declarator))
    return node_consolidate_pointers(pointer, declarator);
    
  return node_binary(NODE_POINTER_DECLARATOR, pointer, declarator);
}

struct node *node_consolidate_pointers(struct node *pointer, struct node *pointer_declarator)
{
  struct node* pointer_head = node_unary_list_head(pointer);
  pointer_head->data.child = pointer_declarator->data.children[0];
  pointer_declarator->data.children[0] = pointer;
  return pointer_declarator;
}

struct node *node_unary_list_head(struct node *unary_node)
{
  struct node *head = unary_node;
  while (head->data.child) head = head->data.child;
  return head;
}