#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "node.h"

extern int yylineno;

/****************
 * CREATE NODES *
 ****************/

/* 
 * these methods are generally called by the parser, 
 * although some of the later passes do create nodes
 * and insert them into the parse tree
 */
 
/* allocate and initialize a generic node */
node *create_node(int node_type) {
  node *n;
  
  n = malloc(sizeof(node));
  assert(NULL != n);

  n->node_type = node_type;
  n->line_number = yylineno;
  return n;
}

node *create_identifier_node(char *id) {
  node *n;
  
  n = create_node(NODE_IDENTIFIER);
  n->data.identifier = (identifier *)malloc(sizeof(identifier));
  assert(NULL != n->data.identifier);
  n->data.identifier->name = id;
  return n;
}

node *create_number_node(unsigned long value, int overflow) {
  node *n;
  
  n = create_node(NODE_NUMBER);
  n->data.number = (number *)malloc(sizeof(number));
  assert(NULL != n->data.number);

  n->data.number->value = value;
  n->data.number->overflow_flag= overflow;

  return n;
}

node *create_unary_operation_node(int operation, node *operand) {
  node *n;
  
  n = create_node(NODE_UNARY_OPERATION);
    
  n->data.unary_operation = malloc(sizeof(unary_operation));
  assert(NULL != n->data.unary_operation);
  
  n->data.unary_operation->operation = operation;
  n->data.unary_operation->operand = operand;

  return n;
}

node *create_binary_operation_node(int operation, node *left_operand, node *right_operand) {
  node *n;
  
  n = create_node(NODE_BINARY_OPERATION);
  
  n->data.binary_operation = malloc(sizeof(binary_operation));
  assert(NULL != n->data.binary_operation);
  
  
  n->data.binary_operation->operation = operation;
  n->data.binary_operation->left_operand = left_operand;
  n->data.binary_operation->right_operand = right_operand;

  return n;
}

node *create_expression_statement_node(node *expression) {
  node *n;
  
  n = create_node(NODE_EXPRESSION_STATEMENT);
  
  n->data.expression_statement = malloc(sizeof(expression_statement));
  assert(NULL != n->data.expression_statement);
  
  n->data.expression_statement->expression = expression;
  return n;
}

node *create_statement_list_node(node *list, node *item) {
  node *n;
  
  n = create_node(NODE_STATEMENT_LIST);
  
  n->data.statement_list = malloc(sizeof(statement_list));
  assert(NULL != n->data.statement_list);
  
  n->data.statement_list->list = list;
  n->data.statement_list->item = item;
  return n;
}

node *create_null_statement_node() {
  node *n;
  
  n = create_node(NODE_NULL_STATEMENT);
  
  return n;
}

/***************************************
 * PARSE TREE PRETTY PRINTER FUNCTIONS *
 ***************************************/

/* 
 * these functions are used to print the parse tree, with normalized formatting
 */


void print_null_statement_node(FILE *output, node *node) {
  assert(NODE_NULL_STATEMENT == node->node_type);
  
  fputs(";", output);
}

void print_statement_list_node(FILE *output, node *node) {
  assert(NODE_STATEMENT_LIST == node->node_type);

  if (NULL != node->data.statement_list->list) {
    print_node(output, node->data.statement_list->list);
  }
  print_node(output, node->data.statement_list->item);
  fputs("\n", output);
}

void print_expression_statement_node(FILE *output, node *node) {
  assert(NODE_EXPRESSION_STATEMENT == node->node_type);
  
  print_node(output, node->data.expression_statement->expression);
  fputs(";", output);
}

void print_binary_operation_node(FILE *output, node *node) {
  static char *binary_operators[] = {
    "+",    /*  0 = ADDITION */
    "-",    /*  1 = SUBTRACTION */
    "="     /*  2 = ASSIGN */          
  };
  assert(NODE_BINARY_OPERATION == node->node_type);
  
  fputs("(", output);

  print_node(output, node->data.binary_operation->left_operand);
  fputs(" ", output);
  fputs(binary_operators[node->data.binary_operation->operation], output);
  fputs(" ", output);
  print_node(output, node->data.binary_operation->right_operand);

  fputs(")", output);
}

void print_unary_operation_node(FILE *output, node *node) {
  static char *unary_operators[] = {
    "+",    /*  2 = UNARY_PLUS */
    "-"     /*  3 = UNARY_MINUS */
  };
  assert(NODE_UNARY_OPERATION == node->node_type);
  
  fputs("(", output);
  fputs(unary_operators[node->data.unary_operation->operation], output);
  print_node(output, node->data.unary_operation->operand);
  fputs(")", output);
}
 
void print_number_node(FILE *output, node *node) {
  assert(NODE_NUMBER == node->node_type);
  
  fprintf(output, "%lu", node->data.number->value);
}


void print_identifier_node(FILE *output, node *node) {
  assert(NODE_IDENTIFIER == node->node_type);

  fputs(node->data.identifier->name, output);  
}

void print_node(FILE *output, node *node) {
  assert(NULL != node);
  
  switch (node->node_type) {
    case NODE_NULL_STATEMENT:
      print_null_statement_node(output, node);
      break;
    case NODE_STATEMENT_LIST:
      print_statement_list_node(output, node);
      break;
    case NODE_EXPRESSION_STATEMENT:
      print_expression_statement_node(output, node);
      break;
    case NODE_UNARY_OPERATION:
      print_unary_operation_node(output, node);
      break;
    case NODE_BINARY_OPERATION:
      print_binary_operation_node(output, node);
      break;
    case NODE_NUMBER:
      print_number_node(output, node);
      break;
    case NODE_IDENTIFIER:
      print_identifier_node(output, node);
      break;
    
    default:
      fprintf(stderr, "print_node called with invalid node type %d\n", node->node_type);
      break;
  }
}