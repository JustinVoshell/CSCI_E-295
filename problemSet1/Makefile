# scanner/Makefile
# Justin Voshell - jvoshell@me.com
# CSCI E295 Spring 2012

# 'all' builds the executable 'scannerCLI' from the generated scanner and the
#       scanner_codes facility.
#
# 'clean' removes all output, including 'scannerCLI'
#
# 'test' runs my test suite
#
# 'section_test' runs the example test suite we were provided in section.

.PHONY : all clean test section_test

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
	@echo "\n\n--------------------------------------------------------------------------------"
	@echo "KEYWORD TEST TEXT:\n\n"
	@cat test/test_all_keywords.txt
	@echo "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	@echo "KEYWORD TEST RESULTS:\n\n"
	@./scannerCLI test/test_all_keywords.txt
	@echo "\n\n--------------------------------------------------------------------------------"
	@echo "OPERATORS TEST TEXT:\n\n"
	@cat test/test_all_operators.txt
	@echo "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	@echo "OPERATORS TEST RESULTS:\n\n"
	@./scannerCLI test/test_all_operators.txt
	@echo "\n\n--------------------------------------------------------------------------------"
	@echo "CHARACTERS TEST TEXT:\n\n"
	@cat test/test_characters.txt
	@echo "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	@echo "CHARACTERS TEST RESULTS:\n\n"
	@./scannerCLI test/test_characters.txt
	@echo "\n\n--------------------------------------------------------------------------------"
	@echo "COMMENTS TEST TEXT:\n\n"
	@cat test/test_comments.txt
	@echo "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	@echo "COMMENTS TEST RESULTS:\n\n"
	@./scannerCLI test/test_comments.txt
	@echo "\n\n--------------------------------------------------------------------------------"
	@echo "IDENTIFIERS TEST TEXT:\n\n"
	@cat test/test_identifiers.txt
	@echo "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	@echo "IDENTIFIERS TEST RESULTS:\n\n"
	@./scannerCLI test/test_identifiers.txt
	@echo "\n\n--------------------------------------------------------------------------------"
	@echo "NUMBERS TEST TEXT:\n\n"
	@cat test/test_numbers.txt
	@echo "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	@echo "NUMBERS TEST RESULTS:\n\n"
	@./scannerCLI test/test_numbers.txt
	@echo "\n\n--------------------------------------------------------------------------------"
	@echo "STRINGS TEST TEXT:\n\n"
	@cat test/test_strings.txt
	@echo "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	@echo "STRINGS TEST RESULTS:\n\n"
	@./scannerCLI test/test_strings.txt

section_test:
	@echo "\n\n--------------------------------------------------------------------------------"
	@echo "2009 TEST TEXT:\n\n"
	@cat test/Willenson_lexer_2009.c
	@echo "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	@echo "2009 TEST RESULTS:\n\n"
	@./scannerCLI test/Willenson_lexer_2009.c
	@echo "\n\n--------------------------------------------------------------------------------"
	@echo "2010 TEST TEXT:\n\n"
	@cat test/Willenson_lexer_2010.c
	@echo "\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "
	@echo "2010 TEST RESULTS:\n\n"
	@./scannerCLI test/Willenson_lexer_2010.c


