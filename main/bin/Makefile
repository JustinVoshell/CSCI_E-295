# bin/Makefile
# Justin Voshell - justin.voshell@me.com
# CSCI E-295 Spring 2012

all : scanner
	@cd $(jhv-test-bin); make all

MODEL_OBJ = codes.o errors.o tokens.o integer.o string_buffer.o
export MODEL_OBJ

MODEL_INC = model/codes.h model/errors.h model/tokens.h model/integer.h model/string_buffer.h
export MODEL_INC

SCANNER_OBJ = scan.o scanner_printer.o
export SCANNER_OBJ

SCANNER_INC = scanner_printer.h
export SCANNER_INC

scanner : $(SCANNER_OBJ) $(MODEL_OBJ)

%.o : scanner/%.c $(SCANNER_INC)
%.o : model/%.c $(MODEL_INC)

clean :
	@rm *.o scanner
	@cd $(jhv-test-bin); make clean

vpath %.c $(jhv-src)/model $(jhv-src)/scanner
vpath %.h $(jhv-include)/model $(jhv-include)/scanner
vpath %.l $(jhv-src)/scanner
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

.PHONY : all clean