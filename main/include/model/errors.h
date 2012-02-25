#ifndef ERRORS_H_JHV9902116
#define ERRORS_H_JHV9902116

#define E_NO_MATCHING_TOKEN	  1001    
#define E_BAD_LITERAL_CHAR    1002 
#define E_UNTERM_CHAR         1003 
#define E_OUT_OF_MEMORY       1004 
#define E_UNTERM_STR          1005 
#define E_BAD_CHAR_ESCAPE     1006 
#define E_BAD_OCTAL_LITERAL   1007 
#define E_EOF_COMMENT         1008 
#define E_EOF_CHAR            1009 
#define E_EOF_STR             1010
#define CODE_TABLE_SIZE       1011

int error_is_EOF(int errorCode);
int error_should_exit(int errorCode);

#endif /*ERRORS_H_JHV9902116*/