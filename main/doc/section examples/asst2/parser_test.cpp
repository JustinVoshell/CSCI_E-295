#include <stdlib.h>

#include "gmock/gmock.h"

extern "C" struct n_node *create_identifier_node(char *);
extern "C" struct n_node *create_number_node(unsigned long, int);
#include "node.h"

#define YYSTYPE node *

#include "parse.h"


class MockScanner {
  public:
    MOCK_METHOD0(yylex, int());
};

MockScanner *mockScanner;

extern "C" int yylex() {
  return mockScanner->yylex();
}
int yylineno = 0;

node *root_node;

extern "C" int yyparse();
extern "C" int yynerrs;

class ParserTest : public ::testing::Test {
  protected:
    MockScanner scanner;
    
  public:
    ParserTest();
    ~ParserTest();
    
    void SetUp();
    void TearDown();
};

ParserTest::ParserTest() { }
ParserTest::~ParserTest() { }

void ParserTest::SetUp() {
  mockScanner = &scanner;
  root_node = NULL;
}

void ParserTest::TearDown() {
  
}

using ::testing::Return;
using ::testing::NotNull;
using ::testing::IsNull;
using ::testing::DoAll;
using ::testing::Assign;
TEST_F(ParserTest, NullStatementTest) {
  EXPECT_CALL(scanner, yylex())
    .WillOnce(Return(SEMICOLON))
    .WillRepeatedly(Return(0));
  
  ASSERT_EQ(0, yyparse());
  ASSERT_THAT(root_node, NotNull());
  ASSERT_EQ(NODE_STATEMENT_LIST, root_node->node_type);
  EXPECT_THAT(root_node->data.statement_list->list, IsNull());
  ASSERT_THAT(root_node->data.statement_list->item, NotNull());
  EXPECT_EQ(NODE_NULL_STATEMENT, root_node->data.statement_list->item->node_type);
}

TEST_F(ParserTest, VarTest) {
  char name[32];
  node *var, *n;
  
  strcpy(name, "a");
  
  var = create_identifier_node(name);
  
  EXPECT_CALL(scanner, yylex())
    .WillOnce(DoAll(Assign(&yylval, var), Return(IDENTIFIER)))
    .WillOnce(Return(SEMICOLON))
    .WillRepeatedly(Return(0));
  
  ASSERT_EQ(0, yyparse());
  ASSERT_THAT(root_node, NotNull());
  ASSERT_EQ(NODE_STATEMENT_LIST, root_node->node_type);
  EXPECT_THAT(root_node->data.statement_list->list, IsNull());

  n = root_node->data.statement_list->item;
  ASSERT_THAT(n, NotNull());
  ASSERT_EQ(NODE_EXPRESSION_STATEMENT, n->node_type);
  ASSERT_EQ(var, n->data.expression_statement->expression);
}

TEST_F(ParserTest, AssignTest) {
  char name[32];
  node *var, *five, *n;
  
  strcpy(name, "a");
  
  var = create_identifier_node(name);
  five = create_number_node(5, 0);
  
  EXPECT_CALL(scanner, yylex())
    .WillOnce(DoAll(Assign(&yylval, var), Return(IDENTIFIER)))
    .WillOnce(Return(EQUALS))
    .WillOnce(DoAll(Assign(&yylval, five), Return(NUMBER)))
    .WillOnce(Return(SEMICOLON))
    .WillRepeatedly(Return(0));
  
  ASSERT_EQ(0, yyparse());
  ASSERT_THAT(root_node, NotNull());
  ASSERT_EQ(NODE_STATEMENT_LIST, root_node->node_type);
  EXPECT_THAT(root_node->data.statement_list->list, IsNull());

  n = root_node->data.statement_list->item;
  ASSERT_THAT(n, NotNull());
  ASSERT_EQ(NODE_EXPRESSION_STATEMENT, n->node_type);

  n = n->data.expression_statement->expression;  
  ASSERT_THAT(n, NotNull());
  ASSERT_EQ(NODE_BINARY_OPERATION, n->node_type);
  
  EXPECT_EQ(ASSIGN, n->data.binary_operation->operation);
  EXPECT_EQ(var, n->data.binary_operation->left_operand);
  EXPECT_EQ(five, n->data.binary_operation->right_operand);
  
}