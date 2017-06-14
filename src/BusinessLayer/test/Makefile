CXX = g++
CPPFILES = BLTest.cpp PresetTest.cpp ConfigTest.cpp ControlTest.cpp \
PlateTest.cpp MoveTest.cpp OrderTest.cpp JSONUtilsTest.cpp
OBJECTS = $(CPPFILES:.cpp=.o)

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR = ../../sharedlibs/googletest

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -isystem $(GTEST_DIR)/include 

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11 --coverage
LIBPATH = -L../../lib -I../../lib/include 
LIBS = -lblhost -lhalhost -lloggerhost -lpthread
# businesslayer depends on hal
# hal+bl depend on logger

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = BLTest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
				$(GTEST_DIR)/include/gtest/internal/*.h

.PHONY: all test test-run clean


# House-keeping build targets.

all : $(TESTS)

test : all

test-run: all
	./BLTest

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o *.gcda *.gcno
	rm -rf logs
	
# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
			$(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
			$(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

%.o : %.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LIBPATH) -c $< -o $@

$(TESTS) : $(OBJECTS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LIBPATH) $^ -o $@ $(LIBS) 
