extern long int yylval;
/* extern unsigned char yytext[]; */
extern int yylex();

enum tokens {RESVWORD, ID, NUMBER, STRING,
             PAREN, BRACKET, BRACE, STMTSEP, INCDEC, LOGNEG, BITWISENEG,
             MULOP, ADDOP, SHIFTOP, RELOP, EQUALOP, BITWISEOP, LOGICALOP,
             CONDITIONAL, ASSIGNOP, SEQUENTIALOP};

  /* kinds of RESVWORDs */
#define RW_BREAK 0
#define RW_CHAR 1
#define RW_CONTINUE 2
#define RW_DO 3
#define RW_ELSE 4
#define RW_FOR 5
#define RW_GOTO 6
#define RW_IF 7
#define RW_INT 8
#define RW_LONG 9
#define RW_RETURN 10
#define RW_SHORT 11
#define RW_SIGNED 12
#define RW_UNSIGNED 13
#define RW_VOID 14
#define RW_WHILE 15

  /* kinds of PARENs */
#define PARENLEFT 0
#define PARENRIGHT 1

  /* kinds of BRACKETs */
#define BRACKETLEFT 0
#define BRACKETRIGHT 1

  /* kinds of BRACEs */
#define BRACELEFT 0
#define BRACERIGHT 1

  /* kinds of STMTSEPs */
#define SEPSEMICOLON 0

  /* kinds of INCDECs */
#define INCDECINCREMENT 0
#define INCDECDECREMENT 1

  /* kinds of LOGNEGs */

  /* kinds of BITWISENEGs */

  /* kinds of MULOPs */
#define MULTIPLY 0
#define DIVIDE 1
#define REMAINDER 2

  /* kinds of ADDOPs */
#define ADDITION 0
#define SUBTRACTION 1

  /* kinds of SHIFTOPs */
#define LEFT 0
#define RIGHT 1

  /* kinds of RELOPs */
#define LT 0
#define LE 1
#define GT 2
#define GE 3

  /* kinds of EQUALOPs */
#define EQ 0
#define NE 1

  /* kinds of BITWISEOPs */
#define BITOR 0
#define BITXOR 1
#define BITAND 2

  /* kinds of LOGICALOPs */
#define LOGICALOR 0
#define LOGICALAND 1

  /* kinds of CONDITIONALs */
#define CONDQUEST 0
#define CONDCOLON 1

  /* kinds of ASSIGNOPs */
#define ASSIGNMENTSIMPLE 0
#define ASSIGNMENTADDITION 1
#define ASSIGNMENTSUBTRACTION 2
#define ASSIGNMENTMULTIPLICATION 3
#define ASSIGNMENTDIVISION 4
#define ASSIGNMENTREMAINDER 5
#define ASSIGNMENTLEFTSHIFT 6
#define ASSIGNMENTRIGHTSHIFT 7
#define ASSIGNMENTBITWISEAND 8
#define ASSIGNMENTBITWISEXOR 9
#define ASSIGNMENTBITWISEOR 10

  /* kinds of SEQUENTIALOPs */
#define SEQUENTIALCOMMA 0
