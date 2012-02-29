#include "ScannerTestBase.h"
#include "gtest/gtest.h"

extern "C" 
{
  #include <stdlib.h>
  #include <stdio.h>
  #include <unistd.h>

  #include "model/node.h"
  #include "model/tokens.h"

  int yylex();
}

extern FILE *yyin;
extern struct node *yylval;
int yylex();

const char *input_filename;
FILE *output_file = stdout;

void ScannerTestBase::SetUp()
{
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  
  yyin = fdopen(fds[0], "r");
  ASSERT_TRUE(yyin);

  test_input = fdopen(fds[1], "w");
  ASSERT_TRUE(test_input);

  input_filename = "test_input";
}

void ScannerTestBase::TearDown()
{
	EXPECT_EQ(0, yylex());
}

void ScannerTestBase::setInput(const char *input_string)
{
  fputs(input_string, test_input);
  fclose(test_input);
}

void ScannerTestBase::scanAndExpectSimpleToken(const int expected_token)
{
  EXPECT_EQ(expected_token, yylex());
  EXPECT_EQ(0ul, yylval);
}

void ScannerTestBase::scanAndExpectIdentifier(const char *expected_name)
{
  ASSERT_EQ(IDENTIFIER, yylex());
  ASSERT_TRUE(yylval);

  expectIdentifier(yylval->data.cstring_value, expected_name);
  free(yylval);
}

void ScannerTestBase::scanAndExpectInteger(const integer_data_type expected_type, const unsigned long expected_value, const integer_data_overflow expected_overflow)
{
  ASSERT_EQ(LITERAL_NUMBER, yylex());
  ASSERT_TRUE(yylval);

  expectInteger(yylval->data.integer_data, expected_type, expected_value, expected_overflow);
  free(yylval);
}

void ScannerTestBase::scanAndExpectString(const char *expected_value, const unsigned short expected_length)
{
  ASSERT_EQ(LITERAL_STRING, yylex());
  ASSERT_TRUE(yylval);

  expectString(yylval->data.string_data, expected_value, expected_length);
  free(yylval);
}

void ScannerTestBase::expectIdentifier(const char *actual, const char *expected_name)
{
  ASSERT_TRUE(actual);
  EXPECT_STREQ(actual, expected_name);
}

void ScannerTestBase::expectInteger(const integer_data *actual, const integer_data_type expected_type, const unsigned long expected_value, const integer_data_overflow expected_overflow)
{
  ASSERT_TRUE(actual);
  EXPECT_EQ(expected_type, actual->type);
  EXPECT_EQ(expected_value, actual->value);
  EXPECT_EQ(expected_overflow, actual->overflow);
}

void ScannerTestBase::expectString(const string_data *actual, const char *expected_value, const unsigned short expected_length)
{
  ASSERT_TRUE(actual);
  ASSERT_EQ(expected_length, actual->length);

  for (unsigned short idx = 0; idx < expected_length; idx++)
  {
    ASSERT_EQ(expected_value[idx], actual->buffer[idx]);
  }
}