#include "ScannerTestBase.h"
#include <stdio.h>
#include <errno.h>
#include "model/tokens.h"
#include "model/integer.h"

extern FILE* yyin;

class ScannerWillenson2009FileTests : public ScannerTestBase 
{
protected:
	static void SetUpTestCase()
	{
		const char* filename = "data/Willenson_lexer_2009.c";
		yyin = fopen(filename, "r");
		ASSERT_TRUE(yyin);
	}
	
	static void TearDownTestCase()
	{
		fclose(yyin);
	}
	
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(ScannerWillenson2009FileTests, Digits)
{
	scanAndExpectInteger(LITERAL_CHAR, 0, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 1, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 2, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 3, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 4, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 5, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 6, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 7, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 8, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_CHAR, 9, NO_OVERFLOW);
}

TEST_F(ScannerWillenson2009FileTests, Letters)
{
	scanAndExpectIdentifier("a");
	scanAndExpectIdentifier("b");
	scanAndExpectIdentifier("c");
	scanAndExpectIdentifier("d");
	scanAndExpectIdentifier("e");
	scanAndExpectIdentifier("f");
	scanAndExpectIdentifier("g");
	scanAndExpectIdentifier("h");
	scanAndExpectIdentifier("i");
	scanAndExpectIdentifier("j");
	scanAndExpectIdentifier("k");
	scanAndExpectIdentifier("l");
	scanAndExpectIdentifier("m");
	scanAndExpectIdentifier("n");
	scanAndExpectIdentifier("o");
	scanAndExpectIdentifier("p");
	scanAndExpectIdentifier("q");
	scanAndExpectIdentifier("r");
	scanAndExpectIdentifier("s");
	scanAndExpectIdentifier("t");
	scanAndExpectIdentifier("u");
	scanAndExpectIdentifier("v");
	scanAndExpectIdentifier("w");
	scanAndExpectIdentifier("x");
	scanAndExpectIdentifier("y");
	scanAndExpectIdentifier("z");
	scanAndExpectIdentifier("A");
	scanAndExpectIdentifier("B");
	scanAndExpectIdentifier("C");
	scanAndExpectIdentifier("D");
	scanAndExpectIdentifier("E");
	scanAndExpectIdentifier("F");
	scanAndExpectIdentifier("G");
	scanAndExpectIdentifier("H");
	scanAndExpectIdentifier("I");
	scanAndExpectIdentifier("J");
	scanAndExpectIdentifier("K");
	scanAndExpectIdentifier("L");
	scanAndExpectIdentifier("M");
	scanAndExpectIdentifier("N");
	scanAndExpectIdentifier("O");
	scanAndExpectIdentifier("P");
	scanAndExpectIdentifier("Q");
	scanAndExpectIdentifier("R");
	scanAndExpectIdentifier("S");
	scanAndExpectIdentifier("T");
	scanAndExpectIdentifier("U");
	scanAndExpectIdentifier("V");
	scanAndExpectIdentifier("W");
	scanAndExpectIdentifier("X");
	scanAndExpectIdentifier("Y");
	scanAndExpectIdentifier("Z");
}

TEST_F(ScannerWillenson2009FileTests, Operators1)
{
	scanAndExpectSimpleToken(LOGICAL_NEGATION);
	scanAndExpectSimpleToken(PLUS);	
	scanAndExpectString("laskjlk", 7);
	scanAndExpectSimpleToken(ASSIGN);
	scanAndExpectSimpleToken(LEFT_BRACE);
	scanAndExpectSimpleToken(REMAINDER);
	scanAndExpectSimpleToken(BITWISE_NEGATION);
	scanAndExpectSimpleToken(RIGHT_BRACE);
	scanAndExpectSimpleToken(BITWISE_XOR);
	scanAndExpectSimpleToken(LEFT_BRACKET);
	scanAndExpectSimpleToken(SEQUENTIAL_EVAL);
	scanAndExpectSimpleToken(BITWISE_AND);
	scanAndExpectSimpleToken(RIGHT_BRACKET);
	scanAndExpectSimpleToken(ASTERISK);
	scanAndExpectSimpleToken(DIVISION);
	scanAndExpectSimpleToken(LESS);
	scanAndExpectSimpleToken(LEFT_PAREN);
	scanAndExpectSimpleToken(BITWISE_OR);
	scanAndExpectSimpleToken(GREATER);
	scanAndExpectSimpleToken(RIGHT_PAREN);
	scanAndExpectSimpleToken(SEMICOLON);
	scanAndExpectInteger(LITERAL_INT, 9, NO_OVERFLOW);
	scanAndExpectSimpleToken(DASH);
	scanAndExpectSimpleToken(COLON);
	scanAndExpectSimpleToken(QUESTION_MARK);
	scanAndExpectIdentifier("_");
}

TEST_F(ScannerWillenson2009FileTests, Strings1)
{
	scanAndExpectString("me`@y'a$ho#o.com", 16);
	scanAndExpectString(" /t /v /n /r ", 13);
}

TEST_F(ScannerWillenson2009FileTests, Identifiers)
{
	scanAndExpectIdentifier("dsjfsk");
	scanAndExpectIdentifier("h76567");
	scanAndExpectInteger(LITERAL_CHAR, 6, NO_OVERFLOW);
	scanAndExpectIdentifier("jhgjh");
	scanAndExpectIdentifier("_jhgj");
	scanAndExpectIdentifier("_87678");
}

TEST_F(ScannerWillenson2009FileTests, Keywords)
{
	scanAndExpectSimpleToken(DO);
	scanAndExpectSimpleToken(FOR);
	scanAndExpectSimpleToken(RETURN);
	scanAndExpectSimpleToken(BREAK);
	scanAndExpectSimpleToken(SHORT);
	scanAndExpectSimpleToken(ELSE);
	scanAndExpectSimpleToken(GOTO);
	scanAndExpectSimpleToken(SIGNED);
	scanAndExpectInteger(LITERAL_INT, 789769876, NO_OVERFLOW);
	scanAndExpectIdentifier("ulnsigned");
	scanAndExpectSimpleToken(CHAR);
	scanAndExpectSimpleToken(IF);
	scanAndExpectSimpleToken(VOID);
	scanAndExpectSimpleToken(INT);
	scanAndExpectSimpleToken(CONTINUE);
	scanAndExpectSimpleToken(LONG);
	scanAndExpectSimpleToken(WHILE);
}

TEST_F(ScannerWillenson2009FileTests, Operators2)
{
	scanAndExpectSimpleToken(LOGICAL_NEGATION);
	scanAndExpectSimpleToken(REMAINDER);
	scanAndExpectSimpleToken(BITWISE_XOR);
	scanAndExpectSimpleToken(BITWISE_AND);
	scanAndExpectSimpleToken(ASTERISK);
	scanAndExpectSimpleToken(DASH);
	scanAndExpectSimpleToken(PLUS);
	scanAndExpectSimpleToken(ASSIGN);
	scanAndExpectSimpleToken(BITWISE_NEGATION);
	scanAndExpectSimpleToken(BITWISE_OR);
	scanAndExpectSimpleToken(LESS);
	scanAndExpectSimpleToken(GREATER);
	scanAndExpectSimpleToken(DIVISION);
	scanAndExpectSimpleToken(QUESTION_MARK);
	scanAndExpectSimpleToken(ASSIGN_SUM);
	scanAndExpectSimpleToken(ASSIGN_DIFFERENCE);
	scanAndExpectSimpleToken(ASSIGN_PRODUCT);
	scanAndExpectSimpleToken(ASSIGN_QUOTIENT);
	scanAndExpectSimpleToken(ASSIGN_REMAINDER);
	scanAndExpectSimpleToken(ASSIGN_LEFT_SHIFT);
	scanAndExpectSimpleToken(ASSIGN_RIGHT_SHIFT);
	scanAndExpectSimpleToken(ASSIGN_BITWISE_AND);
	scanAndExpectSimpleToken(ASSIGN_BITWISE_XOR);
	scanAndExpectSimpleToken(ASSIGN_BITWISE_OR);
	scanAndExpectSimpleToken(INCREMENT);
	scanAndExpectSimpleToken(DECREMENT);
	scanAndExpectSimpleToken(LEFT_SHIFT);
	scanAndExpectSimpleToken(RIGHT_SHIFT);
	scanAndExpectSimpleToken(LESS_OR_EQUAL);
	scanAndExpectSimpleToken(GREATER_OR_EQUAL);
	scanAndExpectSimpleToken(EQUAL_TO);
	scanAndExpectSimpleToken(NOT_EQUAL);
	scanAndExpectSimpleToken(LOGICAL_AND);
	scanAndExpectSimpleToken(LOGICAL_OR);
	scanAndExpectSimpleToken(LEFT_PAREN);
	scanAndExpectSimpleToken(RIGHT_PAREN);
	scanAndExpectSimpleToken(LEFT_BRACKET);
	scanAndExpectSimpleToken(RIGHT_BRACKET);
	scanAndExpectSimpleToken(LEFT_BRACE);
	scanAndExpectSimpleToken(RIGHT_BRACE);
	scanAndExpectSimpleToken(SEQUENTIAL_EVAL);
	scanAndExpectSimpleToken(SEMICOLON);
	scanAndExpectSimpleToken(COLON);
}

TEST_F(ScannerWillenson2009FileTests, IntegerLiterals)
{
	scanAndExpectInteger(LITERAL_SHORT,      6767, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT,   326498724, NO_OVERFLOW);
}

TEST_F(ScannerWillenson2009FileTests, CharacterLiterals)
{
	scanAndExpectInteger(LITERAL_INT, 50, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 97, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT,  9, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 10, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT,  8, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 13, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 12, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 11, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 92, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 39, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 34, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT,  7, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 63, NO_OVERFLOW);
	scanAndExpectInteger(LITERAL_INT, 65, NO_OVERFLOW);
}

TEST_F(ScannerWillenson2009FileTests, StringLiterals)
{
	scanAndExpectString("3825jh", 6);
	scanAndExpectString("sj;asd2", 7);
	scanAndExpectString("sj;asda", 7);
	scanAndExpectString("sj;asd\t", 7);
	scanAndExpectString("sj;asd\n", 7);
	scanAndExpectString("sj;asd\b", 7);
	scanAndExpectString("sj;asd\r", 7);
	scanAndExpectString("sj;asd\f", 7);
	scanAndExpectString("sj;asd\v", 7);
	scanAndExpectString("sj;asd\\", 7);
	scanAndExpectString("sj;asd\"", 7);
	scanAndExpectString("sj;asd\"", 7);
	scanAndExpectString("sj;asd\a", 7);
	scanAndExpectString("sj;asd?", 7);
	scanAndExpectString("sj'`;asd\101", 9);	
}

TEST_F(ScannerWillenson2009FileTests, Leftovers)
{
	scanAndExpectIdentifier("abbaface");
	scanAndExpectSimpleToken(ASTERISK);
	scanAndExpectSimpleToken(DIVISION);
	scanAndExpectInteger(LITERAL_SHORT, 1425, NO_OVERFLOW);
}