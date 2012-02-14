# scanner/Makefile
# Justin Voshell - jvoshell@me.com
# CSCI E295 Spring 2012

.PHONY : all clean test

all : scannerCLI
scannerCLI : scanner.o scanner_codes.o scannerCLI.o
scanner_codes.o : scanner.h scanner_codes.h
scanner.o : scanner.h scanner_codes.h

%.c : %.lex
	$(LEX) $(LEXFLAGS) -o $@ $<

CC = gcc
CFLAGS += -g -Wall -Wextra -pedantic
LINK.o = $(CC) $(LDFLAGS) $(TARGET_ARCH)
LDLIBS += -lfl -ll -lpthread
LEX = flex
LEXFLAGS +=

clean :
	rm -f *.o scannerCLI
	rm -f *~ *#

test :
	cat test/test_all_keywords.txt
	./scannerCLI test/test_all_keywords.txt
	cat test/test_all_operators.txt
	./scannerCLI test/test_all_operators.txt
	cat test/test_characters.txt
	./scannerCLI test/test_characters.txt
	cat test/test_comments.txt
	./scannerCLI test/test_comments.txt
	cat test/test_identifiers.txt
	./scannerCLI test/test_identifiers.txt
	cat test/test_numbers.txt
	./scannerCLI test/test_numbers.txt
	cat test/test_strings.txt
	./scannerCLI test/test_strings.txt

