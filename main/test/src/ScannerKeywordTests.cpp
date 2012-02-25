#include "ScannerTestBase.h"
#include "tokens.h"

class ScannerKeywordTests : public ScannerTestBase {};

TEST_F(ScannerKeywordTests, Break)    { setInput("break");    scanAndExpectSimpleToken(BREAK);    }
TEST_F(ScannerKeywordTests, Char)     { setInput("char");     scanAndExpectSimpleToken(CHAR);     }
TEST_F(ScannerKeywordTests, Continue) { setInput("continue"); scanAndExpectSimpleToken(CONTINUE); }
TEST_F(ScannerKeywordTests, Do)       { setInput("do");       scanAndExpectSimpleToken(DO);       }
TEST_F(ScannerKeywordTests, Else)     { setInput("else");     scanAndExpectSimpleToken(ELSE);     }
TEST_F(ScannerKeywordTests, For)      { setInput("for");      scanAndExpectSimpleToken(FOR);      }
TEST_F(ScannerKeywordTests, Goto)     { setInput("goto");     scanAndExpectSimpleToken(GOTO);     }
TEST_F(ScannerKeywordTests, If)       { setInput("if");       scanAndExpectSimpleToken(IF);       }
TEST_F(ScannerKeywordTests, Int)      { setInput("int");      scanAndExpectSimpleToken(INT);      }
TEST_F(ScannerKeywordTests, Long)     { setInput("long");     scanAndExpectSimpleToken(LONG);     }
TEST_F(ScannerKeywordTests, Return)   { setInput("return");   scanAndExpectSimpleToken(RETURN);   }
TEST_F(ScannerKeywordTests, Short)    { setInput("short");    scanAndExpectSimpleToken(SHORT);    }
TEST_F(ScannerKeywordTests, Signed)   { setInput("signed");   scanAndExpectSimpleToken(SIGNED);   }
TEST_F(ScannerKeywordTests, Unsigned) { setInput("unsigned"); scanAndExpectSimpleToken(UNSIGNED); }
TEST_F(ScannerKeywordTests, Void)     { setInput("void");     scanAndExpectSimpleToken(VOID);     }
TEST_F(ScannerKeywordTests, While)    { setInput("while");    scanAndExpectSimpleToken(WHILE);    }