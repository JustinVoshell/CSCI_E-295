#include "model/error_type.h"

int error_type_is_eof(enum error_type error_type)
{
	return (error_type == ERROR_EOF_COMMENT ||
	        error_type == ERROR_EOF_CHAR    ||
					error_type == ERROR_EOF_STR) ? 1 : 0;
}

int error_type_requires_exit(enum error_type error_type)
{
	return (error_type == ERROR_OUT_OF_MEMORY || error_type_is_eof(error_type)) ? 1 : 0;
}