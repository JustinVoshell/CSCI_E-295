# bin/Makefile
# Justin Voshell - justin.voshell@me.com
# CSCI E-295 Spring 2012

all : scanner parser
	@cd $(jhv-test-bin); make all

MODEL_OBJ = codes.o errors.o tokens.o integer.o string_buffer.o node.o
export MODEL_OBJ

MODEL_INC = codes.h errors.h tokens.h integer.h string_buffer.h node.h
export MODEL_INC

SCANNER_OBJ = scan.o scanner_printer.o
export SCANNER_OBJ

SCANNER_INC = scanner_printer.h
export SCANNER_INC

PARSER_OBJ = parse.o parser_scan.o parser_printer.o  
export PARSER_OBJ

PARSER_INC = parser_printer.h 
export PARSER_INC

scanner : $(SCANNER_OBJ) $(MODEL_OBJ)
parser : $(PARSER_OBJ) $(MODEL_OBJ)

%.o : scanner/%.c $(SCANNER_INC)
%.o : parser/%.c $(PARSER_INC)
%.o : model/%.c $(MODEL_INC)

%.c : %.y
	$(YACC.y) -o $@ $<

clean :
	@rm *.o *.h *.output scanner parser
	@cd $(jhv-test-bin); make clean

vpath %.c $(jhv-src)/model $(jhv-src)/scanner $(jhv-src)/parser 
vpath %.h $(jhv-include)/model $(jhv-include)/scanner $(jhv-include)/parser $(jhv-src)/parser
vpath %.l $(jhv-src)/scanner $(jhv-src)/parser
vpath %.y $(jhv-src)/parser

# COMPILE.c
CC = gcc
CFLAGS += -g -Wall -Wextra -pedantic
CPPFLAGS += -I $(jhv-include) -I $(jhv-include)/model -I $(jhv-include)/scanner

# LINK.o
LDLIBS += -lfl -ll -pthread 

# COMPILE.l
LEX = flex
LEXFLAGS +=

#COMPILE.y
YACC = bison
YFLAGS += -d

.PHONY : all clean