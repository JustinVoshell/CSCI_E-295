#ifndef INTEGER_H_JHV9902116
#define INTEGER_H_JHV9902116

#define LITERAL_CHAR_MAX           255 
#define LITERAL_SHORT_MAX        65535            
#define LITERAL_INT_MAX     2147483647 
#define LITERAL_ULONG_MAX 4294967295ul 

typedef enum
{
  LITERAL_CHAR = 10,
  LITERAL_SHORT,
	LITERAL_INT,
	LITERAL_ULONG
} integer_representation;

enum integer_type
{
	INTEGER_TYPE_VOID = 0,
	INTEGER_TYPE_SIGNED_CHAR,
	INTEGER_TYPE_UNSIGNED_CHAR,
	INTEGER_TYPE_SIGNED_SHORT,
	INTEGER_TYPE_UNSIGNED_SHORT,
	INTEGER_TYPE_SIGNED_INT,
	INTEGER_TYPE_UNSIGNED_INT,
	INTEGER_TYPE_SIGNED_LONG,
	INTEGER_TYPE_UNSIGNED_LONG
};

typedef enum
{
	NO_OVERFLOW = 0,
	HAS_OVERFLOW
} overflow;

typedef struct
{
  unsigned long value;
	integer_representation type;
  overflow overflow_flag;
} integer;

integer* integer_from_cstring(const char* text);
integer* integer_from_char(const int charValue);
integer* integer_from_octal_char(const char* text);

#endif /*INTEGER_H_JHV9902116*/
