%verbose
%debug
%error-verbose

%{

  #include <stdio.h>
  #include "node.h"

  int yylex();
  extern int yylineno;
  void yyerror(char const *s);

  #define YYSTYPE node *

  extern node *root_node;

%}

%token IDENTIFIER
%token NUMBER

%token MINUS PLUS EQUALS

%token LEFT_PAREN RIGHT_PAREN
%token SEMICOLON

%start root

%%

additive_expr           : unary_expr
                        | additive_expr PLUS unary_expr                     { $$ = create_binary_operation_node(ADDITION, $1, $3); }
                        | additive_expr MINUS unary_expr                    { $$ = create_binary_operation_node(SUBTRACTION, $1, $3); }
;

assignment_expr         : additive_expr
                        | identifier EQUALS assignment_expr                 { $$ = create_binary_operation_node(ASSIGN, $1, $3); }
;

expr                    : assignment_expr
;

identifier              : IDENTIFIER                                        
;

primary_expr            : identifier
                        | NUMBER                                            
                        | LEFT_PAREN expr RIGHT_PAREN                       { $$ = $2; }
;

statement               : expr SEMICOLON                                    { $$ = create_expression_statement_node($1); }
                        | SEMICOLON                                         { $$ = create_null_statement_node(); }                            

                        /* ERROR PRODUCTION */
                        | error SEMICOLON
;

statement_list          : statement                                         { $$ = create_statement_list_node(NULL, $1); }
                        | statement_list statement                          { $$ = create_statement_list_node($1, $2); }
;

root                    : statement_list                                    { root_node = $1; }
;

unary_expr              : primary_expr
                        | MINUS unary_expr                                  { $$ = create_unary_operation_node(UNARY_MINUS, $2); }
                        | PLUS unary_expr                                   { $$ = create_unary_operation_node(UNARY_PLUS, $2); }
;

%%

void yyerror(char const *s) {
  fprintf(stderr, "ERROR at line %d: %s\n", yylineno, s);
}

