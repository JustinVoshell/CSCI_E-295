# bin/Makefile
# Justin Voshell - justin.voshell@me.com
# CSCI E-295 Spring 2012

model_objects := node.o integer_data.o string_data.o error_type.o
model_includes := node.h integer_data.h string_data.h error_type.h 
MODEL_INCLUDES := $(model_includes) resource.h tokens.h
export MODEL_INCLUDES

scanner_objects := scanner_scan.o scanner_resource.o 
SCANNER_OBJECTS := $(scanner_objects) $(model_objects)
export SCANNER_OBJECTS

parser_objects := parser_parse.o parser_scan.o parser_resource.o
PARSER_OBJECTS := $(parser_objects) $(model_objects)
export PARSER_OBJECTS

$(model_objects): $(model_includes)

$(scanner_objects): scanner_%.o: %.c 
	$(COMPILE.c) -o $@ $<

$(parser_objects): parser_%.o: %.c
	$(COMPILE.c) -o $@ $<

%.c : %.l
	$(LEX) $(LFLAGS) -o $@ $<

%.c : %.y
	$(YACC.y) -o $@ $<

clean :
	@rm *.o *.h *.c *.output scanner parser
	@cd $(jhv-test-bin); make clean

vpath %.c $(jhv-src)/model $(jhv-src)/scanner $(jhv-src)/parser 
vpath %.h $(jhv-include) $(jhv-include)/model $(jhv-include)/scanner $(jhv-include)/parser $(jhv-bin)
vpath %.l $(jhv-src)/scanner $(jhv-src)/parser
vpath %.y $(jhv-src)/parser

# COMPILE.c
CC = gcc
CFLAGS += -g -Wall -Wextra -pedantic
CPPFLAGS += -I $(jhv-include) -I $(jhv-bin)

# LINK.o
LDLIBS += -lfl -ll -pthread

# COMPILE.l
LEX = flex
LEXFLAGS +=

#COMPILE.y
YACC = bison
YFLAGS += -d

.PHONY : all clean test

all: scanner parser
	@cd $(jhv-test-bin); make all

test: scanner
	@cd $(jhv-test-bin); make test
	
scanner: scanner_printer.o $(SCANNER_OBJECTS)
scanner: LDFLAGS += -DSTANDALONE_SCANNER

scanner.o: CPPFLAGS += -DSTANDALONE_SCANNER
scanner.o: scanner_printer.h $(SCANNER_OBJECTS) $(MODEL_INCLUDES)

scanner_printer.o: CPPFLAGS += -DSTANDALONE_SCANNER
scanner_printer.o: scanner_printer.h $(SCANNER_OBJECTS) $(MODEL_INCLUDES)

parser: parser_printer.o $(PARSER_OBJECTS)
parser.o: parser_printer.h $(PARSER_OBJECTS) $(MODEL_INCLUDES) parse.h
parser_printer.o: parser_printer.h $(PARSER_OBJECTS) $(MODEL_INCLUDES) parse.h