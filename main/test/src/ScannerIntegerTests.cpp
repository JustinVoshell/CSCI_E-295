#include "ScannerTestBase.h"

class ScannerIntegerTests : public ScannerTestBase {};

/* 0 > (2**8 - 1) => char */
TEST_F(ScannerIntegerTests, CharFrom211) { setInput("211"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 211, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, CharFrom255) { setInput("255"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 255, INTEGER_DATA_NO_OVERFLOW); }

/* 2**8 -> (2**16 - 1) => short */
TEST_F(ScannerIntegerTests, ShortFrom256  ) { setInput("256"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 256, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, ShortFrom65534) { setInput("65534"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 65534, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, ShortFrom65535) { setInput("65535"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 65535, INTEGER_DATA_NO_OVERFLOW); }

/* 2**16 -> (2**31 - 1) => int */
TEST_F(ScannerIntegerTests, IntFrom65536     ) { setInput("65536"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 65536, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, IntFrom2147483647) { setInput("2147483647"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 2147483647, INTEGER_DATA_NO_OVERFLOW); }

/* 2**31 -> (2**32 - 1) => unsigned long */
TEST_F(ScannerIntegerTests, ULongFrom2147483648) { setInput("2147483648"); scanAndExpectInteger(INTEGER_DATA_UNSIGNED_LONG, 2147483648, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, ULongFrom4294967295) { setInput("4294967295"); scanAndExpectInteger(INTEGER_DATA_UNSIGNED_LONG, 4294967295, INTEGER_DATA_NO_OVERFLOW); }

/* 2**32 and above => overflow */
TEST_F(ScannerIntegerTests, Overflow4294967296 ) { setInput("4294967296"); scanAndExpectInteger(INTEGER_DATA_UNSIGNED_LONG, 0, INTEGER_DATA_OVERFLOW); }
TEST_F(ScannerIntegerTests, Overflow99999999999) { setInput("99999999999"); scanAndExpectInteger(INTEGER_DATA_UNSIGNED_LONG, 0, INTEGER_DATA_OVERFLOW); }

/* Zero handling */
TEST_F(ScannerIntegerTests, ZeroHandling1)
{
	setInput("0123 1023 10 01 001");
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 123, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 1023, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 10, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 1, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 1, INTEGER_DATA_NO_OVERFLOW);
}
TEST_F(ScannerIntegerTests, ZeroHandling2)
{
	setInput("00100100 001101101");
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 100100, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 1101101, INTEGER_DATA_NO_OVERFLOW);
}

/* Huge number */
TEST_F(ScannerIntegerTests, HugeNumber) 
{
	setInput("9999999999999999999999999999999999999999999"); 
	scanAndExpectInteger(INTEGER_DATA_UNSIGNED_LONG, 0, INTEGER_DATA_OVERFLOW);
}

/* Handle line breaks*/
TEST_F(ScannerIntegerTests, WithLineBreaks)
{
	setInput("12\n3\n00123 123 \n 0123 1 2 \n3");
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 12, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 3, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 123, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 123, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 0, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 123, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 1, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 2, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 3, INTEGER_DATA_NO_OVERFLOW);
}