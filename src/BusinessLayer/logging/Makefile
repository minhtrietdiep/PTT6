# test for logging
# REMEMBER TO USE THE TAB CHARACTER FOR MAKEFILES
# Copy the next thing: "	"
CC	    = g++
CFLAGS  = -I. -std=c++11
DEPS    = logger.h
TARGET  = test
OBJ     = test.o logger.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(TARGET)	
	rm -f $(OBJ)
