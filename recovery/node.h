#ifndef NODE_H_JHV9902116
#define NODE_H_JHV9902116

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

enum error_type
{
	ERROR_NO_MATCHING_TOKEN = 1001,
	ERROR_BAD_LITERAL_CHAR,
	ERROR_UNTERM_CHAR,
	ERROR_OUT_OF_MEMORY,
	ERROR_UNTERM_STR,
	ERROR_BAD_CHAR_ESCAPE,
	ERROR_BAD_OCTAL_ESCAPE,
	ERROR_EOF_COMMENT,
	ERROR_EOF_CHAR,
	ERROR_EOF_STR
};

enum integer_type
{
	INTEGER_TYPE_VOID = 1100,
	INTEGER_TYPE_SIGNED_CHAR,
	INTEGER_TYPE_UNSIGNED_CHAR,
	INTEGER_TYPE_SIGNED_SHORT,
	INTEGER_TYPE_UNSIGNED_SHORT,
	INTEGER_TYPE_SIGNED_INT,
	INTEGER_TYPE_UNSIGNED_INT,
	INTEGER_TYPE_SIGNED_LONG,
	INTEGER_TYPE_UNSIGNED_LONG
};

enum integer_data_overflow
{
	INTEGER_DATA_NO_OVERFLOW = 1110,
	INTEGER_DATA_OVERFLOW
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
		enum integer_type integer_type;
		
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

struct integer_data
{
	unsigned long value;
	enum integer_type type;
	enum integer_data_overflow overflow;
};

struct list_data
{
	struct node *current;
	struct node *next;
};

struct string_data
{
  char* buffer;
  unsigned short length;
  unsigned short size;
};

struct node *node_declaration(struct node *type_specifier, struct node *declarator);
struct node *node_declaration_list(struct node *declaration_list, struct node *declaration);
struct node *node_declarator(struct node *pointer, struct node *declarator);
struct node *node_declarator_list(struct node *declarator_list, struct node *declarator);
struct node *node_direct_declarator(struct node* identifier);
struct node *node_error(enum error_type error_type);
struct node *node_identifier(const char*);
struct node *node_literal_string(struct string_data *literal_string);
struct node *node_literal_integer(struct integer_data *literal_integer);
struct node *node_pointer(struct node* pointer);
struct node *node_type_specifier(enum integer_type);

#endif /*NODE_H_JHV9902116*/
