jhv-src := $(PWD)/src
export jhv-src

jhv-include := $(PWD)/include
export jhv-include

jhv-test := $(PWD)/test
export jhv-test

jhv-bin := $(PWD)/bin
export jhv-bin

jhv-test-bin := $(PWD)/bin/test
export jhv-test-bin

jhv-redist-gtest := $(PWD)/redist/gtest-1.6.0
export jhv-redist-gtest

parser:
	@cd $(jhv-bin); make parser;

scanner:
	@cd $(jhv-bin); make scanner;

all : 
	@cd $(jhv-bin); make all

clean :
	@cd $(jhv-bin); make clean

test : 
	@cd $(jhv-bin); make test

.PHONY : all clean test