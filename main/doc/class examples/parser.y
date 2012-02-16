%{
#include <stdio.h>

enum node_type {NODE_OPERATOR, NODE_NUMBER};

struct node {
  enum node_type type;
  char *operator;
  struct node *left, *right;
  int val;
};

struct node *malloc_op_node(char *operator,
			    struct node *child_left,
			    struct node *child_right);
void *malloc_number_node(int val);
void print_tree(struct node *node_p);
%}

%start line

%token RW_BREAK RW_CHAR RW_CONTINUE RW_DO RW_ELSE RW_FOR RW_GOTO RW_IF RW_INT RW_LONG RW_RETURN RW_SHORT RW_SIGNED RW_UNSIGNED RW_VOID RW_WHILE
%token ID
%token NUMBER
%token STRING
%token SEQUENTIALOP_COMMA
%token ASSIGNOP_SIMPLE ASSIGNOP_ADDITION ASSIGNOP_SUBTRACTION ASSIGNOP_MULTIPLICATION ASSIGNOP_DIVISION ASSIGNOP_REMAINDER ASSIGNOP_LEFTSHIFT ASSIGNOP_RIGHTSHIFT ASSIGNOP_BITWISEAND ASSIGNOP_BITWISEXOR ASSIGNOP_BITWISEOR
%token CONDITIONAL_QUEST CONDITIONAL_COLON
%token LOGICALOP_OR LOGICALOP_AND
%token BITWISEOP_OR BITWISEOP_XOR BITWISEOP_AND
%token EQUALOP_EQ EQUALOP_NE
%token RELOP_LT RELOP_LE RELOP_GT RELOP_GE
%token SHIFTOP_LEFT SHIFTOP_RIGHT
%token ADDOP_ADDITION ADDOP_SUBTRACTION
%token MULOP_MULTIPLY MULOP_DIVIDE MULOP_REMAINDER
%token BITWISENEG
%token LOGNEG
%token INCDEC_INCREMENT INCDEC_DECREMENT
%token STMTSEP_SEMICOLON
%token BRACE_LEFT BRACE_RIGHT
%token BRACKET_LEFT BRACKET_RIGHT
%token PAREN_LEFT PAREN_RIGHT

%left ADDOP_ADDITION
%left MULOP_MULTIPLY
%%
line   : expr STMTSEP_SEMICOLON      { print_tree((struct node *)$1);
                                       printf("\n"); }
;

expr   : expr ADDOP_ADDITION term    { $$ = (long)malloc_op_node("+",
						 (struct node *)$1,
						 (struct node *)$3); }
       | term
       ;

term   : term MULOP_MULTIPLY factor  { $$ = (long)malloc_op_node("*",
						 (struct node *)$1,
						 (struct node *)$3); }
       | factor
       ;

factor : PAREN_LEFT expr PAREN_RIGHT { $$ = $2; }
       | NUMBER                      { $$ = (long)malloc_number_node($1); }
       ;

%%
#include <stdio.h>
#include <stdlib.h>
#include "lex.yy.c"

struct node *malloc_op_node(char *operator,
			    struct node *child_left,
			    struct node *child_right) {
  struct node *node_p;

  node_p = malloc(sizeof(struct node));
#ifdef DEBUG
  printf("malloc_op_node: Parser building op_node with operator %s;\n\tat address 0x%8x\n",
	 operator, node_p);
#endif
  if(node_p == NULL) {
    printf("***Out of memory***\n");
  } else {
    node_p->type = NODE_OPERATOR;
    node_p->operator = operator;
    node_p->left = child_left;
    node_p->right = child_right;
  }

  return node_p;
}

void *malloc_number_node(int val) {
  struct node *node_p;

  node_p = malloc(sizeof(struct node));
#ifdef DEBUG
  printf("malloc_number_node: Parser building number_node with value %d;\n\tat address 0x%8x\n",
	 val, node_p);
#endif
  if(node_p == NULL) {
    printf("***Out of memory***\n");
  } else {
    node_p->type = NODE_NUMBER;
    node_p->val = val;
  }

  return node_p;
}

void print_tree(struct node *node_p) {
  if(node_p->type == NODE_NUMBER) {
    printf("0x%8x: Node NUMBER, Value %d\n", node_p, node_p->val);
  } else {
    printf("0x%8x: Node OPERATOR, Operator %s, Left child 0x%8x, Right child 0x%8x\n",
	   node_p, node_p->operator, node_p->left, node_p->right);
    print_tree(node_p->left);
    print_tree(node_p->right);
  }
}

main() {
  return yyparse();
}

yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}
