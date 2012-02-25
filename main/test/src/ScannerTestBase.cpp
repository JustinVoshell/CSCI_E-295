#include "ScannerTestBase.h"
#include "gtest/gtest.h"

extern "C" {
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "model/tokens.h"
#include "model/integer.h"
#include "model/string_buffer.h"
	int yylex();
}

void* yylval;
extern FILE* yyin;

void ScannerTestBase::SetUp()
{
  int fds[2];
  ASSERT_EQ(0, pipe(fds));
  
  yyin = fdopen(fds[0], "r");
  ASSERT_TRUE(yyin);

  test_input = fdopen(fds[1], "w");
  ASSERT_TRUE(test_input);	
}

void ScannerTestBase::TearDown()
{
	EXPECT_EQ(0, yylex());
}

void ScannerTestBase::setInput(const char* input_string)
{
	fputs(input_string, test_input);
	fclose(test_input);
}
	
void ScannerTestBase::scanAndExpectSimpleToken(const int expected_token)
{
	EXPECT_EQ(expected_token, yylex());
  EXPECT_EQ(0ul, yylval);
}

void ScannerTestBase::scanAndExpectIdentifier(const char* expectedValue)
{
	ASSERT_EQ(IDENTIFIER, yylex());
	expectIdentifier((const char*)yylval, expectedValue);
	free(yylval);
}

void ScannerTestBase::scanAndExpectInteger(const integer_representation expectedType, const unsigned long expectedValue, const overflow expectedOverflow)
{		
	ASSERT_EQ(LITERAL_NUMBER, yylex());
	expectInteger((integer*)yylval, expectedType, expectedValue, expectedOverflow);
	free(yylval);
}

void ScannerTestBase::scanAndExpectString(const char* expectedString, const unsigned long expectedLength)
{
	ASSERT_EQ(LITERAL_STRING, yylex());
	expectString((string*)yylval, expectedString, expectedLength);
	free(yylval);
}	

void ScannerTestBase::expectIdentifier(const char* actualIdentifier, const char* expectedIdentifier)
{
	if (0 == actualIdentifier)
	{
		ADD_FAILURE();
		return;
	}
	
	ASSERT_STREQ(expectedIdentifier, actualIdentifier);
}

void ScannerTestBase::expectInteger(integer* actualInteger, const integer_representation expectedType, const unsigned long expectedValue, const overflow expectedOverflow)
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
}

void ScannerTestBase::expectString(string* actualString, const char* expectedString, const unsigned long expectedLength)
{
	if (0 == actualString)
	{
		ADD_FAILURE();
		return;
	}
	
	ASSERT_EQ(actualString->length, expectedLength);
	for (unsigned long idx = 0; idx < expectedLength; idx++)
	{
		ASSERT_EQ(actualString->buffer[idx], expectedString[idx]);
	}
}