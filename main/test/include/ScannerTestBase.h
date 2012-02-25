#ifndef SCANNERTESTBASE_H
#define SCANNERTESTBASE_H

#include "gtest/gtest.h"

extern "C" {
#include "integer_attribute.h"
#include "string_attribute.h"
}

class ScannerTestBase : public ::testing::Test
{
protected:
	FILE* test_input;

	virtual void SetUp();
	virtual void TearDown();

	void setInput(const char* input_string);
		
	void scanAndExpectSimpleToken(const int expected_token);
	void scanAndExpectIdentifier(const char* expectedValue);
	void scanAndExpectInteger(const integer_representation expectedType, const unsigned long expectedValue, const overflow expectedOverflow);
	void scanAndExpectString(const char* expectedValue, const unsigned long expectedLength);

private:
	void expectIdentifier(const char* actual, const char* expectedValue);
	void expectInteger(integer* actual, const integer_representation expectedType, const unsigned long expectedValue, const overflow expectedOverflow);
	void expectString(string* actual, const char* expectedValue, const unsigned long expectedLength);
};

#endif /*SCANNERTESTBASE_H*/