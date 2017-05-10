CFLAGS=-O2 -Wall -std=c++11
GFLAGS=-O0 -Wall -std=c++11 -g
SOURCES=JSONParser.cpp ClientMessage.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../lib/ -I ../lib/include
LIBS=
LIBSTARGET=-ljsonparser
LIBSHOST=-ljsonparserhost
OUTPUT=jsonparser
lib-target:
	cp Error.h ../lib/include
	cp $(SOURCES:.cpp=.h) ../lib/include
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}.a ${OBJECTS} -c
	rm -f $(OBJECTS)
lib-host:
	cp Error.h ../lib/include
	cp $(SOURCES:.cpp=.h) ../lib/include
	g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}host.a ${OBJECTS} -c
	rm -f $(OBJECTS)
lib-host-g:
	cp Error.h ../lib/include
	cp $(SOURCES:.cpp=.h) ../lib/include
	g++ ${GFLAGS}  ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}host.a ${OBJECTS} -c
	rm -f $(OBJECTS)
all:
	make lib-target
	make lib-host
clean:
	rm -f *.out
	rm -f *.o
	rm -f ../lib/lib${OUTPUT}.a
	rm -f ../lib/lib${OUTPUT}host.a
