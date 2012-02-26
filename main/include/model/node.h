#ifndef NODE_H_JHV9902116
#define NODE_H_JHV9902116

#include "model/integer.h"
#include "model/string_buffer.h"

enum node_type
{
	NODE_DECLARATION,
	NODE_DECLARATION_LIST,
	NODE_DECLARATOR_LIST,
	NODE_ERROR,	
	NODE_IDENTIFIER,
	NODE_LITERAL_INTEGER,
	NODE_LITERAL_STRING,
	NODE_POINTER,
	NODE_TYPE_SPECIFIER
};

struct declaration_data;
struct list_data;

struct node
{
	enum node_type node_type;
	int line_number;
	
	union node_data
	{
		enum integer_type e_integer_type;

		struct declaration_data *declaration;
		struct list_data *list;
		struct node *pointer_to;
		
		integer* literal_integer;
		string* literal_string;

		int error_code;
		const char *name;
	} data;
};

struct declaration_data
{
	struct node *type_specifier;
	struct node *declarator;
};

struct list_data
{
	struct node *current;
	struct node *next;
};

struct node *root_node; 
struct node *node_declaration(struct node *type_specifier, struct node *declarator);
struct node *node_declaration_list(struct node *declaration_list, struct node *declaration);
struct node *node_declarator(struct node *pointer, struct node *direct_declarator);
struct node *node_declarator_list(struct node *declarator_list, struct node *declarator);
struct node *node_direct_declarator(struct node* identifier);
struct node *node_error(int error_code);
struct node *node_identifier(const char*);
struct node *node_literal_string(string* literal_string);
struct node *node_literal_integer(integer* literal_integer);
struct node *node_pointer(struct node* pointer);
struct node *node_type_specifier(enum integer_type);

#endif /*NODE_H_JHV9902116*/