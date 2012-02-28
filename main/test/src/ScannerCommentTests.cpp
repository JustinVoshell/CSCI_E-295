#include "ScannerTestBase.h"
#include "model/integer_data.h"

class ScannerCommentTests : public ScannerTestBase {};

TEST_F(ScannerCommentTests, LineStart)
{
	setInput("/*X*/A\n/*X */B\n/* X*/C\n /*X*/D");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("B");
	scanAndExpectIdentifier("C");
	scanAndExpectIdentifier("D");
}

TEST_F(ScannerCommentTests, LineEnd)
{
	setInput("A/*X*/\nB /*X*/\nC/* X*/\nD/* X */ \n");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("B");
	scanAndExpectIdentifier("C");
	scanAndExpectIdentifier("D");
}

TEST_F(ScannerCommentTests, MidLine)
{
	setInput("A/*X*/A\nB /*X*/B\n C /*X*/ C\nD /* X */ D \n");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("B");
	scanAndExpectIdentifier("B");
	scanAndExpectIdentifier("C");
	scanAndExpectIdentifier("C");
	scanAndExpectIdentifier("D");
	scanAndExpectIdentifier("D");
}

TEST_F(ScannerCommentTests, MultiLine)
{
	setInput("A/*XX XX\n XX XX \nXX*/B /* \n\n*/ C/*\n\n*//*\n\n*/D");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("B");
	scanAndExpectIdentifier("C");
	scanAndExpectIdentifier("D");	
}

TEST_F(ScannerCommentTests, EmbeddedAsterisks)
{
	setInput("A/* **/B/**\n*\n**/C/**/D/*- -* *-**/E");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("B");
	scanAndExpectIdentifier("C");
	scanAndExpectIdentifier("D");
	scanAndExpectIdentifier("E");
}

TEST_F(ScannerCommentTests, LeavesOneSpace)
{
	setInput("A/**/A B/*   */B 12/**/34 56/*\n*/78");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("B");
	scanAndExpectIdentifier("B");
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 12, INTEGER_DATA_NO_OVERFLOW);	
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 34, INTEGER_DATA_NO_OVERFLOW);	
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 56, INTEGER_DATA_NO_OVERFLOW);	
	scanAndExpectInteger(INTEGER_DATA_SIGNED_INT, 78, INTEGER_DATA_NO_OVERFLOW);	
}