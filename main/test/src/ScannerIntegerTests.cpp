#include "ScannerTestBase.h"

class ScannerIntegerTests : public ScannerTestBase {};

/* 0 > (2**8 - 1) => char */
TEST_F(ScannerIntegerTests, CharFrom211) { setInput("211"); scanAndExpectInteger(LITERAL_CHAR, 211, NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, CharFrom255) { setInput("255"); scanAndExpectInteger(LITERAL_CHAR, 255, NO_OVERFLOW); }

/* 2**8 -> (2**16 - 1) => short */
TEST_F(ScannerIntegerTests, ShortFrom256  ) { setInput("256"); scanAndExpectInteger(LITERAL_SHORT, 256, NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, ShortFrom65534) { setInput("65534"); scanAndExpectInteger(LITERAL_SHORT, 65534, NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, ShortFrom65535) { setInput("65535"); scanAndExpectInteger(LITERAL_SHORT, 65535, NO_OVERFLOW); }

/* 2**16 -> (2**31 - 1) => int */
TEST_F(ScannerIntegerTests, IntFrom65536     ) { setInput("65536"); scanAndExpectInteger(LITERAL_INT, 65536, NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, IntFrom2147483647) { setInput("2147483647"); scanAndExpectInteger(LITERAL_INT, 2147483647, NO_OVERFLOW); }

/* 2**31 -> (2**32 - 1) => unsigned long */
TEST_F(ScannerIntegerTests, ULongFrom2147483648) { setInput("2147483648"); scanAndExpectInteger(LITERAL_ULONG, 2147483648, NO_OVERFLOW); }
TEST_F(ScannerIntegerTests, ULongFrom4294967295) { setInput("4294967295"); scanAndExpectInteger(LITERAL_ULONG, 4294967295, NO_OVERFLOW); }

/* 2**32 and above => overflow */
TEST_F(ScannerIntegerTests, Overflow4294967296 ) { setInput("4294967296"); scanAndExpectInteger(LITERAL_ULONG, LITERAL_ULONG_MAX, HAS_OVERFLOW); }
TEST_F(ScannerIntegerTests, Overflow99999999999) { setInput("99999999999"); scanAndExpectInteger(LITERAL_ULONG, LITERAL_ULONG_MAX, HAS_OVERFLOW); }

/* Zero handling */
TEST_F(ScannerIntegerTests, ZeroHandling1)
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
TEST_F(ScannerIntegerTests, ZeroHandling2)
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
TEST_F(ScannerIntegerTests, HugeNumber) { setInput("9999999999999999999999999999999999999999999"); scanAndExpectInteger(LITERAL_ULONG, LITERAL_ULONG_MAX, HAS_OVERFLOW); }

/* Handle line breaks*/
TEST_F(ScannerIntegerTests, WithLineBreaks)
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