#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define boolean int

// Grammar:

// <expr> ::=	<expr> <additive-op> <term> |
//	<term>
// <term> ::=	<term> <multiplicative-op> <factor> |
//	<factor>
// <factor> ::= "(" <expr> ")" |
//	<integer>
// <additive_op> ::=	"+" | "-"
// <multiplicative_op> ::=	"*" | "/" | "%"
// <integer> ::=  <digit> |
//	<digit> <integer>
// <digit> ::=	  "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

// Eliminate left recursion by applying the rule:
//
//			A ::= A <alpha> | <beta>
//
//	becomes:	A ::= <beta> A'
//			A' ::= <alpha> A' |
//				nothing

// <expr> ::=	<term> <expr-prime>
// <expr-prime> ::=	<additive-op> <term> <expr-prime> |
//	nothing
// <term> ::=	<factor> <term-prime>
// <term-prime> ::=	<multiplicative-op> <factor> <term-prime> |
//	nothing
// <factor> ::= "(" <expr> ")" |
//	<integer>
// <additive_op> ::=	"+" | "-"
// <multiplicative_op> ::=	"*" | "/" | "%"
// <integer> ::=  <digit> |
//	<digit> <integer>
// <digit> ::=	  "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

enum ops {
  OP_MUL = 1, OP_DIV = 2, OP_REM = 3, OP_ADD = 4, OP_SUB = 5
} op;

const static int PLACE_VALUE = 10;

const static boolean DEBUG = TRUE;

static int val;

static char readChar();
static void unread(char ch);
static boolean integer();
static boolean factor();
static boolean term_prime();
static boolean term();
static boolean expr_prime();
static boolean expr();
static boolean multiplicative_op();
static boolean additive_op();
int main(int argc, char *argv[]);

static char readChar() {
  char ch;
	
  ch = getchar();

  return ch;
}

static void unread(char ch) {
  ungetc(ch, stdin);
}

static boolean integer() {
  char ch;

  if(DEBUG) {
    printf("Looking for an <integer>\n");
  }
	
  ch = readChar();
  if((ch >= '0') && (ch <= '9')) {
    val = ch-'0';
    while(TRUE) {
      ch = readChar();
      if((ch < '0') || (ch > '9')) {
	unread(ch);
	return TRUE;
      }
      val = val*PLACE_VALUE + ch-'0';
    }
  } else {
    unread(ch);
    return FALSE;
  }
}

static boolean factor() {
  char ch;
	
  if(DEBUG) {
    printf("Looking for a <factor>\n");
  }
	
  ch = readChar();
  if(ch == '(') {
    if(expr()) {
      ch = readChar();
      if(ch == ')') {
	return TRUE;
      } else { // if(ch == ')')
	printf("<expr> not followed by right parenthesis in <factor>\n");
	return FALSE;
      }
    } else { // if(expr())
      printf("Left parenthesis not followed by <expr> in <factor>\n");
      return FALSE;
    }
  } else { // if(ch == '(')
    unread(ch);
    if(integer()) {
      return TRUE;
    } else {
      printf("<integer> not found in <factor>\n");
      return FALSE;
    }
  }
}

static boolean term_prime() {
  if(DEBUG) {
    printf("Looking for a <term-prime>\n");
  }
	
  if(multiplicative_op()) {
    if(factor()) {
      if(term_prime()) {
	return TRUE;
      } else {
	printf("<factor> not followed by <term-prime> in <term-prime>\n");
	return FALSE;
      }
    } else {
      printf("<multiplicative-op> not followed by <factor> in <term-prime>\n");
      return FALSE;
    }
  } else {
    return TRUE;
  }
}

static boolean term() {
  if(DEBUG) {
    printf("Looking for a <term>\n");
  }
	
  if(factor()) {
    if(term_prime()) {
      return TRUE;
    } else {
      printf("<factor> not followed by <term-prime> in <term>\n");
      return FALSE;
    }
  } else {
    printf("<factor> not found in <term>\n");
    return FALSE;
  }
}

static boolean expr_prime() {
  if(DEBUG) {
    printf("Looking for an <expr-prime>\n");
  }
	
  if(additive_op()) {
    if(term()) {
      if(expr_prime()) {
	return TRUE;
      } else {
	printf("<term> not followed by <expr-prime> in <expr-prime>\n");
	return FALSE;
      }
    } else {
      printf("<additive-op> not followed by <term> in <expr-prime>\n");
      return FALSE;
    }
  } else {
    return TRUE;
  }
}

static boolean expr() {
  if(DEBUG) {
    printf("Looking for an <expr>\n");
  }
	
  if(term()) {
    if(expr_prime()) {
      return TRUE;
    } else {
      printf("<term> not followed by <expr-prime> in <expr>\n");
      return FALSE;
    }
  } else {
    printf("<term> not found in <expr>\n");
    return FALSE;
  }
}

static boolean multiplicative_op() {
  char ch;

  if(DEBUG) {
    printf("Looking for a <multiplicative-op>\n");
  }

  ch = readChar();
  if(ch == '*') {
    op = OP_MUL;
    return TRUE;
  } else if (ch == '/') {
    op = OP_DIV;
    return TRUE;
  } else if (ch == '%') {
    op = OP_REM;
    return TRUE;
  } else {
    unread(ch);
    return FALSE;
  }
}

static boolean additive_op() {
  char ch;

  if(DEBUG) {
    printf("Looking for an <additive-op>\n");
  }
	
  ch = readChar();
  if(ch == '+') {
    op = OP_ADD;
    return TRUE;
  } else if (ch == '-') {
    op = OP_SUB;
    return TRUE;
  } else {
    unread(ch);
    return FALSE;
  }
}

int main(int argc, char *argv[]) {
  printf("Please enter an expression: ");
  fflush(stdout);
  if(expr()) {
    printf("Successfully parsed a well-formed <expr>\n");
  } else {
    printf("Malformed <expr>\n");
  }
  return 1;
}
