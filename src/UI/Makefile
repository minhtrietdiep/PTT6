CFLAGS=-O2 -Wall -std=c++11
SOURCES=
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../../lib -I ../../lib/include
LIBS=-lstdc++ -lpthread -lrt
LIBSTARGET=-lcommunication -llogger
LIBSHOST=-lcommunicationhost -lloggerhost
OUTPUT=communication

lib-target:


lib-host:


target:

host:

test:

all:
	make lib-target
	make lib-host
	make target
	make host
	make mqread

clean:
	rm -f *.out
	rm -f *.o
	rm -f ../../lib/lib${OUTPUT}.a
	rm -f ../../lib/lib${OUTPUT}host.a
