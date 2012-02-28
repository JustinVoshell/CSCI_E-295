#ifndef SCANNERTESTBASE_H
#define SCANNERTESTBASE_H

#include "gtest/gtest.h"

extern "C" 
{
	#include "model/node.h"
}

class ScannerTestBase : public ::testing::Test
{
protected:
	FILE* test_input;

	virtual void SetUp();
	virtual void TearDown();

	void setInput(const char* input_string);
		
	void scanAndExpectSimpleToken(const int expected_token);
	void scanAndExpectIdentifier(const char *expected_name);
	void scanAndExpectInteger(const integer_data_type expected_type, const unsigned long expected_value, const integer_data_overflow expected_overflow);
	void scanAndExpectString(const char *expected_value, const unsigned short expected_length);

private:
	void expectIdentifier(const char *actual, const char* expected_name);
	void expectInteger(const integer_data *actual, const integer_data_type expected_type, const unsigned long expected_value, const integer_data_overflow expected_overflow);
	void expectString(const string_data *actual, const char *expected_value, const unsigned short expected_length);
};

#endif /*SCANNERTESTBASE_H*/