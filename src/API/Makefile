CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=Control.cpp API.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=API.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)