#include "tokens.h"

int token_has_attribute(int token)
{
	return (IDENTIFIER == token ||
	        LITERAL_NUMBER == token ||
					LITERAL_STRING == token) ? 1 : 0;
}