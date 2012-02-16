#ifndef _NODE_H
#define _NODE_H

#include <stdio.h>


/* node types */
#define NODE_NUMBER                          0
#define NODE_IDENTIFIER                      1
#define NODE_UNARY_OPERATION                 2
#define NODE_BINARY_OPERATION                3
#define NODE_EXPRESSION_STATEMENT            4
#define NODE_STATEMENT_LIST                  5
#define NODE_NULL_STATEMENT                  6
typedef struct n_node {
  int node_type;
  int line_number;
  union {
    struct n_number *number;
    struct n_identifier *identifier;
    struct n_unary_operation *unary_operation;
    struct n_binary_operation *binary_operation;
    struct n_expression_statement *expression_statement;
    struct n_list *statement_list;
  } data;
} node;

typedef struct n_number {
  unsigned long value;
  int overflow;
} number;

typedef struct n_identifier {
  char *name;
} identifier;

typedef struct n_list {
  node *list;
  node *item;
} statement_list;

typedef struct n_expression_statement {
  node *expression;
} expression_statement;


/* unary operations */
#define UNARY_PLUS        0
#define UNARY_MINUS       1
typedef struct n_unary_operation {
  int operation;
  node *operand;
} unary_operation;

/*binary operations */
#define ADDITION                 0
#define SUBTRACTION              1
#define ASSIGN                   2
typedef struct n_binary_operation {
  int operation;
  node *left_operand;
  node *right_operand;
} binary_operation;

node *create_null_statement_node();

node *create_statement_list_node(node *list, node *item);

node *create_expression_statement_node(node *expression);

node *create_binary_operation_node(int operation, node *left_operand, node *right_operand);

node *create_number_node(unsigned long value, int overflow);
node *create_identifier_node(char *id);

node *create_unary_operation_node(int operation, node *operand);

void print_node(FILE *output, node *root);

node *get_identifier_from_declarator(node *declarator);

#endif
