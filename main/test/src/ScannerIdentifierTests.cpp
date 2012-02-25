#include "ScannerTestBase.h"
#include "model/integer.h"

class ScannerIdentifierTests : public ScannerTestBase {};

TEST_F(ScannerIdentifierTests, Letters)
{
	setInput("a aa A aA AA Aa");
	scanAndExpectIdentifier("a");
	scanAndExpectIdentifier("aa");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("aA");
	scanAndExpectIdentifier("AA");
	scanAndExpectIdentifier("Aa");
}

TEST_F(ScannerIdentifierTests, LettersAndNumbers)
{
	setInput("a1 a1234567890 aa2 A3 aA4 AA5 Aa6 31st 0a0a0");
	scanAndExpectIdentifier("a1");
	scanAndExpectIdentifier("a1234567890");
	scanAndExpectIdentifier("aa2");
	scanAndExpectIdentifier("A3");
	scanAndExpectIdentifier("aA4");
	scanAndExpectIdentifier("AA5");
	scanAndExpectIdentifier("Aa6");
	scanAndExpectInteger(LITERAL_CHAR, 31, NO_OVERFLOW);
	scanAndExpectIdentifier("st");
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectIdentifier("a0a0");
}

TEST_F(ScannerIdentifierTests, Underscores)
{
	setInput("_a _aa _A _aA _AA _Aa _1 a_ a_a A_ AA_ AAA_ A_AA a1___ ____1 0_a_1");
	scanAndExpectIdentifier("_a");
	scanAndExpectIdentifier("_aa");
	scanAndExpectIdentifier("_A");
	scanAndExpectIdentifier("_aA");
	scanAndExpectIdentifier("_AA");
	scanAndExpectIdentifier("_Aa");
	scanAndExpectIdentifier("_1");
	scanAndExpectIdentifier("a_");
	scanAndExpectIdentifier("a_a");
	scanAndExpectIdentifier("A_");
	scanAndExpectIdentifier("AA_");
	scanAndExpectIdentifier("AAA_");
	scanAndExpectIdentifier("A_AA");
	scanAndExpectIdentifier("a1___");
	scanAndExpectIdentifier("____1");
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectIdentifier("_a_1");
}