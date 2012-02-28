#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "node.h"

extern int yylineno;

struct node *node_factory(enum node_type type)
{
	struct node *new_node = malloc(sizeof(struct node));
	assert(new_node);
	
	new_node->node_type = type;
	new_node->line_number = yylineno;
	return new_node;
}

struct node *node_array_declarator(struct node *declarator, struct node *length)
{
	struct node *new_node;
	struct array_declarator_data *array_declarator = malloc(sizeof(struct array_declarator_data));
	assert(array_declarator);
	
	array_declarator->declarator = declarator;
	array_declarator->length = length;
	
	new_node = node_factory(NODE_ARRAY_DECLARATOR);
	new_node->data.array_declarator = array_declarator;
	return new_node;
}

struct node *node_declaration(struct node *type_specifier, struct node *declarator)
{
	struct node *new_node;
	struct declaration_data *declaration = malloc(sizeof(struct declaration_data));
	assert(declaration);
	
	declaration->type_specifier = type_specifier;
	declaration->declarator = declarator;
	
	new_node = node_factory(NODE_DECLARATION);
	new_node->data.declaration = declaration;
	return new_node;
}

struct node *node_declaration_list(struct node *child_declaration_list, struct node *declaration)
{
	struct node *new_node;
	struct list_data *declaration_list = malloc(sizeof(struct list_data));
	assert(declaration_list);
	
	declaration_list->current = declaration;
	declaration_list->next = child_declaration_list;
	
	new_node = node_factory(NODE_DECLARATION_LIST);
	new_node->data.list = declaration_list;
	return new_node;
}

struct node *node_declarator(struct node *pointer, struct node *direct_declarator)
{
	struct node *pointer_tail;
	if (pointer)
	{
		pointer_tail = pointer;
		while (pointer_tail->data.pointer_to)
		{
			pointer_tail = pointer_tail->data.pointer_to;
		}
		pointer_tail->data.pointer_to = direct_declarator;
		return pointer;
	}
	return direct_declarator;
}

struct node *node_declarator_list(struct node *child_declarator_list, struct node *declarator)
{
	struct node *new_node;
	struct list_data *declarator_list = malloc(sizeof(struct list_data));
	assert(declarator_list);
	
	declarator_list->current = declarator;
	declarator_list->next = child_declarator_list;
	
	new_node = node_factory(NODE_DECLARATOR_LIST);
	new_node->data.list = declarator_list;
	return new_node;
}

struct node *node_direct_declarator(struct node *identifier)
{
	return identifier;
}

struct node *node_error(enum error_type error_type)
{
	struct node *new_node = node_factory(NODE_ERROR);
	new_node->data.error_type = error_type;
	return new_node;
}

struct node *node_identifier(const char *name)
{
	struct node *new_node = node_factory(NODE_IDENTIFIER);
	new_node->data.name = name;
	return new_node;
}

struct node *node_literal_integer(struct integer_data *literal_integer)
{
	struct node *new_node = node_factory(NODE_LITERAL_INTEGER);
	new_node->data.integer = literal_integer;
	return new_node;
}

struct node *node_literal_string(struct string_data *literal_string)
{
	struct node *new_node = node_factory(NODE_LITERAL_STRING);
	new_node->data.string = literal_string;
	return new_node;
}

struct node *node_pointer(struct node *pointer)
{
	struct node *new_node = node_factory(NODE_POINTER);
	if (pointer) new_node->data.pointer_to = pointer;
	return new_node;
}

struct node *node_type_specifier(enum integer_type integer_type)
{
	struct node *new_node = node_factory(NODE_TYPE_SPECIFIER);
	new_node->data.integer_type = integer_type;
	return new_node;
}
