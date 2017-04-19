CFLAGS=-O2 -Wall -std=c++11
SOURCES=Thread.cpp CommunicationServer.cpp MessageQueue.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../lib -I ../lib
LIBS=-lstdc++ -lpthread -lrt
LIBSTARGET=-lcommunication -llogger
LIBSHOST=-lcommunicationhost -lloggerhost
OUTPUT=communication

lib-target:
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}.a ${OBJECTS} -c
	rm -f $(OBJECTS)

lib-host:
	g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}host.a ${OBJECTS} -c
	rm -f $(OBJECTS)

target:
	make lib-target
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}.out main.cpp ${LIBSTARGET} ${LIBS}

host:
	make lib-host
	g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}-host.out main.cpp ${LIBSHOST} ${LIBS}

mqread:
	g++ ${CFLAGS} ${LIBPATH} -w -o mqread-host.out mqread.cpp ${LIBSHOST} ${LIBS}
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -w -o mqread.out mqread.cpp ${LIBSTARGET} ${LIBS}

all:
	make lib-target
	make lib-host
	make target
	make host
	make mqread

clean:
	rm -f *.out
	rm -f *.o
	rm -f ../lib/lib${OUTPUT}.a
	rm -f ../lib/lib${OUTPUT}host.a