#ifndef INTEGER_DATA_H_JHV9902116
#define INTEGER_DATA_H_JHV9902116

enum integer_data_type
{
	INTEGER_DATA_VOID = 1100,
	INTEGER_DATA_SIGNED_CHAR,
	INTEGER_DATA_UNSIGNED_CHAR,
	INTEGER_DATA_SIGNED_SHORT,
	INTEGER_DATA_UNSIGNED_SHORT,
	INTEGER_DATA_SIGNED_INT,
	INTEGER_DATA_UNSIGNED_INT,
	INTEGER_DATA_SIGNED_LONG,
	INTEGER_DATA_UNSIGNED_LONG
};

#define INTEGER_DATA_UNSIGNED_CHAR_MAX  255           
#define INTEGER_DATA_SIGNED_INT_MAX     2147483647 
#define INTEGER_DATA_UNSIGNED_LONG_MAX  4294967295ul 

enum integer_data_overflow
{
	INTEGER_DATA_NO_OVERFLOW = 1110,
	INTEGER_DATA_OVERFLOW
};

struct integer_data
{
	unsigned long value;
	enum integer_data_type type;
	enum integer_data_overflow overflow;
};

struct integer_data *integer_data_from_cstring(const char *text);
struct integer_data *integer_data_from_char(const int value);
struct integer_data *integer_data_from_octal_char(const char *text);

#endif /*INTEGER_DATA_H_JHV9902116*/