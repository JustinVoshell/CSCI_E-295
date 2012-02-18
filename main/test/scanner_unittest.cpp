#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "gtest/gtest.h"
#include "scanner_codes.h"
#include "scanner.h"

unsigned long yylval;
extern FILE* yyin;
extern "C" int yylex();

using namespace testing;
class ScannerTest : public ::testing::Test
{
protected:
  FILE* test_input;

  void SetUp()
  {
    int fds[2];
    ASSERT_EQ(0, pipe(fds));
    
    yyin = fdopen(fds[0], "r");
    ASSERT_TRUE(yyin);

    test_input = fdopen(fds[1], "w");
    ASSERT_TRUE(test_input);
  }

  void TearDown() {}

  void ExpectTokenOnly(int token, const char* input)
  {
    fputs(input, test_input);
    fclose(test_input);

    EXPECT_EQ(token, yylex());
    EXPECT_EQ(0ul, yylval);
    EXPECT_EQ(0, yylex());
  }

  void ExpectIntegerConstant(int type, int overflow, int value, const char* input)
  {
    fputs(input, test_input);
    fclose(test_input);
    
    integer_t* attribute;
    attribute = (integer_t*)yylval;
    EXPECT_EQ(attribute->value, value);
    EXPECT_EQ(attribute->type, type);
    EXPECT_EQ(attribute->overflow, overflow);
    free(attribute);
  }
};

TEST_F(ScannerTest, AsteriskTest)
{
  ExpectTokenOnly(ASTERISK, "*");
}

TEST_F(ScannerTest, IntegerLessThanCharTest)
{
  ExpectIntegerConstant(CHAR, 0, 211, "211");
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
