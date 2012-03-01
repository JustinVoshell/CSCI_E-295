#ifndef NODE_H_JHV9902116
#define NODE_H_JHV9902116

#include "model/error_type.h"
#include "model/integer_data.h"
#include "model/string_data.h"

enum node_type
{
	NODE_ROOT,
	NODE_TRANSLATION_UNIT,
	NODE_TOP_LEVEL_DECLARATION,
	NODE_DECLARATION,
	NODE_DECLARATION_SPECIFIERS,
	NODE_TYPE_SPECIFIER,
	NODE_INTEGER_TYPE_SPECIFIER,
	NODE_SIGNED_TYPE_SPECIFIER,
	NODE_UNSIGNED_TYPE_SPECIFIER,
	NODE_VOID_TYPE_SPECIFIER,
	NODE_IDECL_LIST,
	NODE_IDECLARATOR,
	NODE_DECLARATOR,
	NODE_POINTER_DECLARATOR,
	NODE_POINTER,
	NODE_DIRECT_DECLARATOR,
	NODE_SIMPLE_DECLARATOR,
	NODE_IDENTIFIER, 
	NODE_LITERAL_STRING,
	NODE_LITERAL_INTEGER,
	NODE_ERROR
};

struct node
{
	enum node_type node_type;
	int line_number;
	
	union node_data
	{
		int int_value; 
		const char* cstring_value; 
		enum error_type error_type;
		struct node *child;
		struct node **children; 
		struct integer_data *integer_data;
		struct string_data *string_data;
	} data;
};
   
struct node *node_basic(enum node_type node_type);
struct node *node_int(enum node_type node_type, int value);
struct node *node_cstring(enum node_type node_type, const char *value);
struct node *node_unary(enum node_type node_type, struct node *child);
struct node *node_binary(enum node_type node_type, struct node *child_left, struct node *child_right);
struct node *node_literal_integer(enum node_type node_type, struct integer_data *integer_data);
struct node *node_literal_string(enum node_type node_type, struct string_data *string_data);
struct node *node_error(enum error_type error_type);

#endif /*NODE_H_JHV9902116*/