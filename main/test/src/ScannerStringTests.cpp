#include "ScannerTestBase.h"

class ScannerStringTests : public ScannerTestBase {};

TEST_F(ScannerStringTests, Simple          ) { setInput("\"This is a string.\""                   ); scanAndExpectString("This is a string.",              17); }
TEST_F(ScannerStringTests, Continuation    ) { setInput("\"This is \\\na string.\""               ); scanAndExpectString("This is a string.",              17); }
TEST_F(ScannerStringTests, CharacterEscapes) { setInput("\"\\n\\t\\b\\r\\f\\v\\a\\?\\\\\\'\\\"\"" ); scanAndExpectString("\012\011\010\015\014\013\007\077\134\047\042", 11); }
TEST_F(ScannerStringTests, OctalEscapes    ) { setInput("\"\\0\\00\\000\\1\\12\\123\\377\\777\""  ); scanAndExpectString("\000\000\000\001\012\123\377\000",8); }
TEST_F(ScannerStringTests, SingleQuotes    ) { setInput("\"Jonathan 'Cinco Ocho' Papelbon\""      ); scanAndExpectString("Jonathan 'Cinco Ocho' Papelbon", 30); }