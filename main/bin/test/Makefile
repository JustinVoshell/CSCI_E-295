# bin/test/Makefile
# Justin Voshell - justin.voshell@me.com
# CSCI E-295 Spring 2012

all : ScannerTests
	@cp -r $(jhv-test)/data .

test : all
	echo $(SCANNER_OBJECTS)
	@./ScannerTests

clean :
	@rm -f *.o ScannerTests
	@rm -rf ./data

SCANNER_TESTS = ScannerTestBase.o ScannerIntegerTests.o ScannerKeywordTests.o ScannerOperatorTests.o ScannerCharacterTests.o ScannerStringTests.o ScannerCommentTests.o ScannerIdentifierTests.o ScannerWillenson2009FileTests.o

ScannerTests : CXXFLAGS += -DSTANDALONE_SCANNER
ScannerTests : ScannerTests.o $(SCANNER_OBJECTS) $(SCANNER_TESTS) gtest.a 

Scanner%Tests.o : ScannerTestBase.h $(SCANNER_OBJECTS) $(MODEL_INCLUDES)
ScannerTestBase.o : ScannerTestBase.h $(SCANNER_OBJECTS) $(MODEL_INCLUDES) 

vpath %.h $(jhv-include) $(jhv-include)/model $(jhv-test)/include $(jhv-redist-gtest)/src
vpath %.o $(jhv-bin)
vpath %.cpp $(jhv-test)/src
vpath %.cc $(jhv-redist-gtest)/src

.PHONY : all clean test

# Make GTEST
# (taken from section example Makefile)

CPP = g++
CXXFLAGS += -g -Wall -Wextra \
	          -I$(jhv-redist-gtest) \
            -I$(jhv-redist-gtest)/include \
            -I$(jhv-include) \
            -I$(jhv-test)/include

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