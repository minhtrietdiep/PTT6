CFLAGS=-O2 -Wall -std=c++11
SOURCES=
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../lib -I ../lib/include -I ../sharedlibs # pls less dirty or something idk
LIBS=-lstdc++ -lpthread -lrt
LIBSTARGET= -lcommunication -llogger -ljsonparser 
LIBSHOST= -lcommunicationhost -lloggerhost -ljsonparserhost 
OUTPUT=mqjson

lib-target:
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}.a ${OBJECTS} -c
	rm -f $(OBJECTS)

lib-host:
	g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}host.a ${OBJECTS} -c
	rm -f $(OBJECTS)

target:
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}.out main.cpp ${LIBSTARGET} ${LIBS}

host:
	g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}-host.out main.cpp ${LIBSHOST} ${LIBS}

all:
	make lib-target
	make lib-host
	make target
	make host

clean:
	rm -f *.out
	rm -f *.o
	rm -f ../lib/lib${OUTPUT}.a
	rm -f ../lib/lib${OUTPUT}host.a

