#ifndef NODE_H_JHV9902116
#define NODE_H_JHV9902116

#include "model/error_type.h"
#include "model/integer_data.h"
#include "model/string_data.h"

enum node_type
{
	NODE_ARRAY_DECLARATOR = 900,
	NODE_DECLARATION,
	NODE_DECLARATION_LIST,
	NODE_DECLARATOR_LIST,
	NODE_ERROR,	
	NODE_FUNCTION_DECLARATOR,
	NODE_IDENTIFIER,
	NODE_LITERAL_INTEGER,
	NODE_LITERAL_STRING,
	NODE_PARAMETER_DECLARATION,
	NODE_PARAMETER_LIST,
	NODE_POINTER,
	NODE_TYPE_SPECIFIER
};

struct node
{
	enum node_type node_type;
	int line_number;
	
	union node_data
	{
		struct array_declarator_data *array_declarator;
		struct declaration_data      *declaration;
		struct integer_data          *integer;
		struct list_data             *list;
		struct node                  *pointer_to;
		struct string_data           *string;

		enum error_type error_type;
		enum integer_data_type integer_type;
		
		int length;
		const char *name;
	} data;
};

struct array_declarator_data
{
	struct node *declarator;
	struct node *length;
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

struct node *node_array_declarator(struct node *declarator, struct node *constant); 
struct node *node_declaration(struct node *type_specifier, struct node *declarator);
struct node *node_declaration_list(struct node *declaration_list, struct node *declaration);
struct node *node_declarator(struct node *pointer, struct node *declarator);
struct node *node_declarator_list(struct node *declarator_list, struct node *declarator);
struct node *node_direct_declarator(struct node* identifier);
struct node *node_error(enum error_type error_type);
struct node *node_function_declarator(struct node *declarator, struct node *parameter_list);
struct node *node_identifier(const char*);
struct node *node_literal_string(struct string_data *literal_string);
struct node *node_literal_integer(struct integer_data *literal_integer);
struct node *node_parameter_declaration(struct node *type_specifier, struct node *declarator);
struct node *node_parameter_list(struct node *parameter_list, struct node *parameter_declaration);
struct node *node_pointer(struct node* pointer);
struct node *node_type_specifier(enum integer_data_type);

#endif /*NODE_H_JHV9902116*/