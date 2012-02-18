# bin/test/Makefile
# Justin Voshell - justin.voshell@me.com
# CSCI E-295 Spring 2012

vpath %.h $(jhv-include) $(jhv-redist-gtest)/src
vpath %.o $(jhv-bin)
vpath %.cpp $(jhv-test)
vpath %.cc $(jhv-redist-gtest)/src
all : scanner_unittest

test :
	@./scanner_unittest

clean :
	rm -f *.o scanner_unittest

.PHONY : all clean test

scanner_unittest : scanner.o gtest.a
scanner_unittest.o : scanner.h scanner_codes.h $(GTEST_HEADERS)

# Make GTEST
# (taken from section example Makefile)

CPP = g++
CXXFLAGS += -g -Wall -Wextra \
	    -I$(jhv-redist-gtest) \
            -I$(jhv-redist-gtest)/include \
            -I$(jhv-include)

LINK.o = $(CXX) $(LDFLAGS) $(TARGET_ARCH)

LDLIBS += -lfl -lpthread

GTEST_HEADERS = $(jhv-redist-gtest)/include/gtest/*.h \
                $(jhv-redist-gtest)/include/gtest/internal/*.h

GTEST_SRCS_ = $(jhv-redist-gtest)/src/*.cc \
              $(jhv-redist-gtest)/src/*.h \
              $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
gtest-main.o : $(GTEST_SRCS_)

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^