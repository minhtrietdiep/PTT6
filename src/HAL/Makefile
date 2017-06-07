CFLAGS=-O2 -Wall -std=c++11
SOURCES=Arm.cpp Drive.cpp Vacuum.cpp HAL.cpp Coordinates.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../lib -I ../lib/include
LIBS=-lstdc++ -lpthread -lrt
LIBSTARGET=-lhal -llogger
LIBSHOST=-lhalhost -lloggerhost
OUTPUT=hal

lib-target:
	cp $(SOURCES:.cpp=.h) ../lib/include
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}.a ${OBJECTS} -c
	rm -f $(OBJECTS)

lib-host:
	cp $(SOURCES:.cpp=.h) ../lib/include
	g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}host.a ${OBJECTS} -c
	rm -f $(OBJECTS)

target:

host:

test:	
	cd test && make clean && make test

test-run:
	cd test && make test-run

test-clean:
	cd test && make clean

copy:

all:
	make lib-target
	make lib-host
	make target
	make host
	make copy

clean:
	rm -f *.out
	rm -f *.o
