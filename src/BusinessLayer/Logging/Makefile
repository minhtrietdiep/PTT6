CFLAGS=-O2 -Wall -std=c++11
SOURCES=Logger.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../../lib -I ../../lib/include
LIBS=
LIBSTARGET=-llogger
LIBSHOST=-lloggerhost
OUTPUT=logger

lib-target:
	cp $(SOURCES:.cpp=.h) ../../lib/include
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../../lib/lib${OUTPUT}.a ${OBJECTS} -c
	rm -f $(OBJECTS)

lib-host:
	cp $(SOURCES:.cpp=.h) ../../lib/include
	g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../../lib/lib${OUTPUT}host.a ${OBJECTS} -c
	rm -f $(OBJECTS)

target:

host:

copy:

all:
	make lib-target
	make lib-host
	make target
	make host
	make test-target
	make test-host
	make copy

clean:
	rm -f *.out
	rm -f *.o
	rm -f ../../lib/lib${OUTPUT}.a
	rm -f ../../lib/lib${OUTPUT}host.a

test-target:
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}.out BanaanTest.cpp main.cpp ${LIBSTARGET} ${LIBS}
	
test-host:
	g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}-host.out BanaanTest.cpp main.cpp ${LIBSHOST} ${LIBS}

