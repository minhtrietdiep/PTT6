CFLAGS=-O2 -Wall -std=c++11
SOURCES=
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../lib -I ../lib/include
LIBS=-lstdc++ -lpthread -lrt
LIBSTARGET=-lcommunication -llogger
LIBSHOST=-lcommunicationhost -lloggerhost
OUTPUT=ui

lib-host-gcov: lib-host

lib-target:

lib-host:

host-gcov: host

target:

host:

test:

test-run:

test-clean:

all:
	make lib-target
	make lib-host
	make target
	make host

clean:
	rm -f *.out
	rm -f *.o
