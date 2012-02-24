# bin/Makefile
# Justin Voshell - justin.voshell@me.com
# CSCI E-295 Spring 2012

all : scannerCLI
scannerCLI : scanner.o code_table.o
code_table.o : code_table.h
scanner.o : code_table.h tokens.h token_attributes.h

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