CC=g++
CFLAGS=-c -Wall 
LDFLAGS=
TESTLDFLAGS=-lpthread -lgtest -lgtest_main -L/usr/lib -pthread
SOURCES=Config.cpp Control.cpp Move.cpp Order.cpp Plate.cpp Preset.cpp Step.cpp BL.cpp
TESTSOURCES=Tests/Test_Config.cpp
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