# bin/test/Makefile
# Justin Voshell - justin.voshell@me.com
# CSCI E-295 Spring 2012

all : UnitTests
	@cp -r $(jhv-test)/data .

test : all
	@./UnitTests

clean :
	@rm -f *.o UnitTests
	@rm -rf ./data

UNIT_TESTS = ScannerTestBase.o ScannerIntegerTests.o ScannerKeywordTests.o ScannerOperatorTests.o ScannerCharacterTests.o ScannerStringTests.o ScannerCommentTests.o ScannerIdentifierTests.o ScannerWillenson2009FileTests.o

UnitTests : $(SCANNER_OBJ) $(MODEL_OBJ) $(UNIT_TESTS) gtest.a 
Scanner%Tests.o : ScannerTestBase.h $(SCANNER_INC) $(MODEL_INC) $(TEST_HEADERS)
ScannerTestBase.o : ScannerTestBase.h $(SCANNER_INC) $(MODEL_INC) $(TEST_HEADERS) 

vpath %.h $(jhv-include) $(jhv-include)/model $(jhv-include)/scanner $(jhv-test)/include $(jhv-redist-gtest)/src
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