# Makefile
# Justin Voshell - jvoshell@me.com
# CSCI E295 Spring 2012

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

all : 
	@cd $(jhv-bin); make all

clean :
	cd $(jhv-bin); make clean
	cd $(jhv-test-bin); make clean

test : all
	@cd $(jhv-test-bin); make all; make test

.PHONY : all clean test
