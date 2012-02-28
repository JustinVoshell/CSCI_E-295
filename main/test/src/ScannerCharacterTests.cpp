#include "ScannerTestBase.h"
#include "model/integer_data.h"

class ScannerCharacterTests : public ScannerTestBase {};

/* Escape characters */
TEST_F(ScannerCharacterTests, NewLine       ) { setInput("\'\\n\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 10, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, HorizontalTab ) { setInput("\'\\t\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  9, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Backspace     ) { setInput("\'\\b\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  8, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, CarriageReturn) { setInput("\'\\r\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 13, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, FormFeed      ) { setInput("\'\\f\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 12, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, VerticalTab   ) { setInput("\'\\v\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 11, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Alert         ) { setInput("\'\\a\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  7, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, QuestionMark  ) { setInput("\'\\?\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 63, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Backslash     ) { setInput("\'\\\\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 92, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, SingleQuote   ) { setInput("\'\\\'\'"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 39, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, DoubleQuote1  ) { setInput("\'\\\"\'"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 34, INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, DoubleQuote2  ) { setInput("\'\"\'"  ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 34, INTEGER_DATA_NO_OVERFLOW); }

/* Octal escapes */
TEST_F(ScannerCharacterTests, Octal0  ) { setInput("\'\\0\'"  ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,   0,  INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal00 ) { setInput("\'\\00\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,   0,  INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal000) { setInput("\'\\000\'"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,   0,  INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal1  ) { setInput("\'\\1\'"  ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,   1,  INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal12 ) { setInput("\'\\12\'" ); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  10,  INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal123) { setInput("\'\\123\'"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  83,  INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal377) { setInput("\'\\377\'"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 255,  INTEGER_DATA_NO_OVERFLOW); }
TEST_F(ScannerCharacterTests, Octal777) { setInput("\'\\777\'"); scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,   0,  INTEGER_DATA_OVERFLOW);    } 

/* Inline */
TEST_F(ScannerCharacterTests, Adjacent)
{
	setInput("\'a\'\'b\' \'\\\'\'\'\\\'\'\'\\\'\'\'c\'\n\'d\'");
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  97, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  98, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  39, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  39, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  39, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT,  99, INTEGER_DATA_NO_OVERFLOW);
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 100, INTEGER_DATA_NO_OVERFLOW);	
}                                         