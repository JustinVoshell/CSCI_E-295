# bin/Makefile
# Justin Voshell - justin.voshell@me.com
# CSCI E-295 Spring 2012

all : scannerCLI
scannerCLI : scanner.o code_table.o integer_attribute.o string_attribute.o
code_table.o : code_table.h tokens.h
integer_attribute.o : integer_attribute.h
string_attribute.o : string_attribute.h integer_attribute.h
scanner.o : code_table.h integer_attribute.h string_attribute.h tokens.h

clean :
	rm *.o scannerCLI

vpath %.c $(jhv-src)
vpath %.h $(jhv-include)
vpath %.l $(jhv-src)
vpath %.y $(jhv-src)

# COMPILE.c
CC = gcc
CFLAGS += -g -Wall -Wextra -pedantic
CPPFLAGS += -I $(jhv-include)

# LINK.o
LDLIBS += -lfl -ll -pthread 

# COMPILE.l
LEX = flex
LEXFLAGS +=

#COMPILE.y
YACC = bison

.PHONY : all clean