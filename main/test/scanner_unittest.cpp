#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "gtest/gtest.h"

#include "tokens.h"
#include "token_attributes.h"

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
 
  void TearDown()
  {
		EXPECT_EQ(0, yylex());
	}
	
	void setInput(const char* input_string)
	{
		fputs(input_string, test_input);
		fclose(test_input);
	}
	
  void scanAndExpectSimpleToken(const int expected_token)
  {
		EXPECT_EQ(expected_token, yylex());
    EXPECT_EQ(0ul, yylval);
  }

	void scanAndExpectInteger(const integer_representation expectedType, const unsigned long expectedValue, const overflow expectedOverflow)
  {		
		EXPECT_EQ(LITERAL_NUMBER, yylex());
		expectAndFreeIntegerAttribute((integer*)yylval, expectedType, expectedValue, expectedOverflow);
  }
	
	void expectAndFreeIntegerAttribute(integer* actualInteger, const integer_representation expectedType, const unsigned long expectedValue, const overflow expectedOverflow)
	{
		if (NULL == actualInteger)
		{
			ADD_FAILURE();
			return;
		}
		
		if (!(0 == expectedOverflow || 1 == expectedOverflow))
		{
			ADD_FAILURE();
		}
	  else
		{			
			EXPECT_EQ(actualInteger->type, expectedType);
			EXPECT_EQ(actualInteger->value, expectedValue);
			EXPECT_EQ(actualInteger->overflow_flag, expectedOverflow);
		}
		
		free(actualInteger);
	}
};

/* 0 > (2**8 - 1) => char */
TEST_F(ScannerTest, CharFrom211) { setInput("211"); scanAndExpectInteger(LITERAL_CHAR, 211, NO_OVERFLOW); }
TEST_F(ScannerTest, CharFrom255) { setInput("255"); scanAndExpectInteger(LITERAL_CHAR, 255, NO_OVERFLOW); }

/* 2**8 -> (2**16 - 1) => short */
TEST_F(ScannerTest, ShortFrom256  ) { setInput("256"); scanAndExpectInteger(LITERAL_SHORT, 256, NO_OVERFLOW); }
TEST_F(ScannerTest, ShortFrom65534) { setInput("65534"); scanAndExpectInteger(LITERAL_SHORT, 65534, NO_OVERFLOW); }
TEST_F(ScannerTest, ShortFrom65535) { setInput("65535"); scanAndExpectInteger(LITERAL_SHORT, 65535, NO_OVERFLOW); }

/* 2**16 -> (2**31 - 1) => int */
TEST_F(ScannerTest, IntFrom65536     ) { setInput("65536"); scanAndExpectInteger(LITERAL_INT, 65536, NO_OVERFLOW); }
TEST_F(ScannerTest, IntFrom2147483647) { setInput("2147483647"); scanAndExpectInteger(LITERAL_INT, 2147483647, NO_OVERFLOW); }

/* 2**31 -> (2**32 - 1) => unsigned long */
TEST_F(ScannerTest, ULongFrom2147483648) { setInput("2147483648"); scanAndExpectInteger(LITERAL_ULONG, 2147483648, NO_OVERFLOW); }
TEST_F(ScannerTest, ULongFrom4294967295) { setInput("4294967295"); scanAndExpectInteger(LITERAL_ULONG, 4294967295, NO_OVERFLOW); }

/* 2**32 and above => overflow */
TEST_F(ScannerTest, Overflow4294967296 ) { setInput("4294967296"); scanAndExpectInteger(LITERAL_ULONG, LITERAL_ULONG_MAX, HAS_OVERFLOW); }
TEST_F(ScannerTest, Overflow99999999999) { setInput("99999999999"); scanAndExpectInteger(LITERAL_ULONG, LITERAL_ULONG_MAX, HAS_OVERFLOW); }

/* Zero handling */
TEST_F(ScannerTest, ZeroHandling1)
{
	setInput("0123 1023 10 01 001");
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 123, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_SHORT, 1023, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 10, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 1, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 1, NO_OVERFLOW);
}
TEST_F(ScannerTest, ZeroHandling2)
{
	setInput("00100100 001101101");
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 100100, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 1101101, NO_OVERFLOW);
}

/* Huge number */
TEST_F(ScannerTest, HugeNumber) { setInput("9999999999999999999999999999999999999999999"); scanAndExpectInteger(LITERAL_ULONG, LITERAL_ULONG_MAX, HAS_OVERFLOW); }

/* Handle line breaks*/
TEST_F(ScannerTest, WithLineBreaks)
{
	setInput("12\n3\n00123 123 \n 0123 1 2 \n3");
	scanAndExpectInteger(LITERAL_CHAR, 12, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 3, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 123, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 123, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 123, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 1, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 2, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 3, NO_OVERFLOW);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
