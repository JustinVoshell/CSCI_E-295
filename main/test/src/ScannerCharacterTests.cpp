#include "ScannerTestBase.h"

extern "C" {
#include "integer_attribute.h"
}

class ScannerCharacterTests : public ScannerTestBase {};

/* Escape characters */
TEST_F(ScannerCharacterTests, NewLine       ) { setInput("\'\\n\'" ); scanAndExpectInteger(LITERAL_INT, 10, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, HorizontalTab ) { setInput("\'\\t\'" ); scanAndExpectInteger(LITERAL_INT,  9, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Backspace     ) { setInput("\'\\b\'" ); scanAndExpectInteger(LITERAL_INT,  8, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, CarriageReturn) { setInput("\'\\r\'" ); scanAndExpectInteger(LITERAL_INT, 13, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, FormFeed      ) { setInput("\'\\f\'" ); scanAndExpectInteger(LITERAL_INT, 12, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, VerticalTab   ) { setInput("\'\\v\'" ); scanAndExpectInteger(LITERAL_INT, 11, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Alert         ) { setInput("\'\\a\'" ); scanAndExpectInteger(LITERAL_INT,  7, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, QuestionMark  ) { setInput("\'\\?\'" ); scanAndExpectInteger(LITERAL_INT, 63, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Backslash     ) { setInput("\'\\\\'" ); scanAndExpectInteger(LITERAL_INT, 92, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, SingleQuote   ) { setInput("\'\\\'\'"); scanAndExpectInteger(LITERAL_INT, 39, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, DoubleQuote1  ) { setInput("\'\\\"\'"); scanAndExpectInteger(LITERAL_INT, 34, NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, DoubleQuote2  ) { setInput("\'\"\'"  ); scanAndExpectInteger(LITERAL_INT, 34, NO_OVERFLOW); }

/* Octal escapes */
TEST_F(ScannerCharacterTests, Octal0  ) { setInput("\'\\0\'"  ); scanAndExpectInteger(LITERAL_INT,   0,  NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal00 ) { setInput("\'\\00\'" ); scanAndExpectInteger(LITERAL_INT,   0,  NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal000) { setInput("\'\\000\'"); scanAndExpectInteger(LITERAL_INT,   0,  NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal1  ) { setInput("\'\\1\'"  ); scanAndExpectInteger(LITERAL_INT,   1,  NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal12 ) { setInput("\'\\12\'" ); scanAndExpectInteger(LITERAL_INT,  10,  NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal123) { setInput("\'\\123\'"); scanAndExpectInteger(LITERAL_INT,  83,  NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal377) { setInput("\'\\377\'"); scanAndExpectInteger(LITERAL_INT, 255,  NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal777) { setInput("\'\\777\'"); scanAndExpectInteger(LITERAL_INT, 255, HAS_OVERFLOW); } 

/* Inline */
TEST_F(ScannerCharacterTests, Adjacent)
{
	setInput("\'a\'\'b\' \'\\\'\'\'\\\'\'\'\\\'\'\'c\'\n\'d\'");
	scanAndExpectInteger(LITERAL_INT,  97, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT,  98, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT,  39, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT,  39, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT,  39, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT,  99, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 100, NO_OVERFLOW);	
}                                         