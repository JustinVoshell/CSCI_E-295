#include "ScannerTestBase.h"
#include "model/tokens.h"

class ScannerOperatorTests : public ScannerTestBase {};

TEST_F(ScannerOperatorTests, Asterisk           ) { setInput("*"  ); scanAndExpectSimpleToken(ASTERISK            ); } 
TEST_F(ScannerOperatorTests, Colon              ) { setInput(":"  ); scanAndExpectSimpleToken(COLON               ); } 
TEST_F(ScannerOperatorTests, Dash               ) { setInput("-"  ); scanAndExpectSimpleToken(DASH                ); } 
TEST_F(ScannerOperatorTests, Plus               ) { setInput("+"  ); scanAndExpectSimpleToken(PLUS                ); } 
TEST_F(ScannerOperatorTests, QuestionMark       ) { setInput("?"  ); scanAndExpectSimpleToken(QUESTION_MARK       ); } 
TEST_F(ScannerOperatorTests, Assign             ) { setInput("="  ); scanAndExpectSimpleToken(ASSIGN              ); } 
TEST_F(ScannerOperatorTests, AssignBitwiseAnd   ) { setInput("&=" ); scanAndExpectSimpleToken(ASSIGN_BITWISE_AND  ); } 
TEST_F(ScannerOperatorTests, AssignBitwiseOr    ) { setInput("|=" ); scanAndExpectSimpleToken(ASSIGN_BITWISE_OR   ); } 
TEST_F(ScannerOperatorTests, AssignBitwiseXor   ) { setInput("^=" ); scanAndExpectSimpleToken(ASSIGN_BITWISE_XOR  ); } 
TEST_F(ScannerOperatorTests, AssignLeftShift    ) { setInput("<<="); scanAndExpectSimpleToken(ASSIGN_LEFT_SHIFT   ); } 
TEST_F(ScannerOperatorTests, AssignRightShift   ) { setInput(">>="); scanAndExpectSimpleToken(ASSIGN_RIGHT_SHIFT  ); } 
TEST_F(ScannerOperatorTests, AssignSum          ) { setInput("+=" ); scanAndExpectSimpleToken(ASSIGN_SUM          ); } 
TEST_F(ScannerOperatorTests, AssignDifference   ) { setInput("-=" ); scanAndExpectSimpleToken(ASSIGN_DIFFERENCE   ); } 
TEST_F(ScannerOperatorTests, AssignProduct      ) { setInput("*=" ); scanAndExpectSimpleToken(ASSIGN_PRODUCT      ); } 
TEST_F(ScannerOperatorTests, AssignQuotient     ) { setInput("/=" ); scanAndExpectSimpleToken(ASSIGN_QUOTIENT     ); } 
TEST_F(ScannerOperatorTests, AssignRemainder    ) { setInput("%=" ); scanAndExpectSimpleToken(ASSIGN_REMAINDER    ); } 
TEST_F(ScannerOperatorTests, BitwiseAnd         ) { setInput("&"  ); scanAndExpectSimpleToken(BITWISE_AND         ); } 
TEST_F(ScannerOperatorTests, BitwiseOr          ) { setInput("|"  ); scanAndExpectSimpleToken(BITWISE_OR          ); } 
TEST_F(ScannerOperatorTests, BitwiseXor         ) { setInput("^"  ); scanAndExpectSimpleToken(BITWISE_XOR         ); } 
TEST_F(ScannerOperatorTests, BitwiseNegation    ) { setInput("~"  ); scanAndExpectSimpleToken(BITWISE_NEGATION    ); } 
TEST_F(ScannerOperatorTests, LeftShift          ) { setInput("<<" ); scanAndExpectSimpleToken(LEFT_SHIFT          ); } 
TEST_F(ScannerOperatorTests, RightShift         ) { setInput(">>" ); scanAndExpectSimpleToken(RIGHT_SHIFT         ); } 
TEST_F(ScannerOperatorTests, Division           ) { setInput("/"  ); scanAndExpectSimpleToken(DIVISION            ); } 
TEST_F(ScannerOperatorTests, Remainder          ) { setInput("%"  ); scanAndExpectSimpleToken(REMAINDER           ); } 
TEST_F(ScannerOperatorTests, Increment          ) { setInput("++" ); scanAndExpectSimpleToken(INCREMENT           ); } 
TEST_F(ScannerOperatorTests, Decrement          ) { setInput("--" ); scanAndExpectSimpleToken(DECREMENT           ); } 
TEST_F(ScannerOperatorTests, Less               ) { setInput("<"  ); scanAndExpectSimpleToken(LESS                ); } 
TEST_F(ScannerOperatorTests, LessOrEqual        ) { setInput("<=" ); scanAndExpectSimpleToken(LESS_OR_EQUAL       ); } 
TEST_F(ScannerOperatorTests, Greater            ) { setInput(">"  ); scanAndExpectSimpleToken(GREATER             ); } 
TEST_F(ScannerOperatorTests, GreaterOrEqual     ) { setInput(">=" ); scanAndExpectSimpleToken(GREATER_OR_EQUAL    ); } 
TEST_F(ScannerOperatorTests, EqualTo            ) { setInput("==" ); scanAndExpectSimpleToken(EQUAL_TO            ); } 
TEST_F(ScannerOperatorTests, NotEqual           ) { setInput("!=" ); scanAndExpectSimpleToken(NOT_EQUAL           ); } 
TEST_F(ScannerOperatorTests, LogicalAnd         ) { setInput("&&" ); scanAndExpectSimpleToken(LOGICAL_AND         ); } 
TEST_F(ScannerOperatorTests, LogicalOr          ) { setInput("||" ); scanAndExpectSimpleToken(LOGICAL_OR          ); } 
TEST_F(ScannerOperatorTests, LogicalNegation    ) { setInput("!"  ); scanAndExpectSimpleToken(LOGICAL_NEGATION    ); } 
TEST_F(ScannerOperatorTests, LeftParen          ) { setInput("("  ); scanAndExpectSimpleToken(LEFT_PAREN          ); } 
TEST_F(ScannerOperatorTests, RightParen         ) { setInput(")"  ); scanAndExpectSimpleToken(RIGHT_PAREN         ); } 
TEST_F(ScannerOperatorTests, LeftBracket        ) { setInput("["  ); scanAndExpectSimpleToken(LEFT_BRACKET        ); } 
TEST_F(ScannerOperatorTests, RightBracket       ) { setInput("]"  ); scanAndExpectSimpleToken(RIGHT_BRACKET       ); } 
TEST_F(ScannerOperatorTests, LeftBrace          ) { setInput("{"  ); scanAndExpectSimpleToken(LEFT_BRACE          ); } 
TEST_F(ScannerOperatorTests, RightBrace         ) { setInput("}"  ); scanAndExpectSimpleToken(RIGHT_BRACE         ); } 
TEST_F(ScannerOperatorTests, StatementTerminator) { setInput(";"  ); scanAndExpectSimpleToken(SEMICOLON           ); } 
TEST_F(ScannerOperatorTests, SequentialEval     ) { setInput(","  ); scanAndExpectSimpleToken(SEQUENTIAL_EVAL     ); } 