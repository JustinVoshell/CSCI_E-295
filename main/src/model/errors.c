#include "errors.h"

int error_is_EOF(int error_code)
{
	return (error_code == E_EOF_COMMENT ||
	        error_code == E_EOF_CHAR    ||
					error_code == E_EOF_STR) ? 1 : 0;
}

int error_should_exit(int error_code)
{
	return (error_code == E_OUT_OF_MEMORY ||
	        error_is_EOF(error_code)) ? 1 : 0;
}