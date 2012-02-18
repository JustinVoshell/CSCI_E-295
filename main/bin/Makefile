# bin/Makefile
# Justin Voshell - justin.voshell@me.com
# CSCI E-295 Spring 2012

all : scannerCLI
scannerCLI : scanner.o scanner_codes.o
scanner_codes.o : scanner.h scanner_codes.h
scanner.o : scanner.h scanner_codes.h

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