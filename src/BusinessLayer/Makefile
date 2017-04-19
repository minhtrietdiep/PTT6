CC=g++
CFLAGS=-c -Wall 
LDFLAGS=
TESTLDFLAGS=-lpthread -lgtest -lgtest_main -L/usr/lib -pthread
SOURCES=$(wildcard *.cpp)
TESTSOURCES=$(wildcard Tests/*.cpp)
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)
OBJECTS=$(SOURCES:.cpp=.o)
TESTEXECUTABLE=Tests/RunTests.out
EXECUTABLE=BL.out

all: source test

source:$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

test: $(TESTSOURCES) $(TESTEXECUTABLE)

$(TESTEXECUTABLE):$(TESTOBJECTS)
	$(CC) $(TESTOBJECTS) $(TESTLDFLAGS)  -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE) $(TESTOBJECTS) $(TESTEXECUTABLE)