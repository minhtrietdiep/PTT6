CFLAGS=-O2 -Wall -std=gnu++11
SOURCES=Thread.cpp CommunicationServer.cpp MessageQueue.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../lib
LIBS=-lstdc++ -lpthread -lrt
LIBSTARGET=-lcommunication -llogger
LIBSHOST=-lcommunicationhost -lloggerhost
OUTPUT=communication

lib-target:
	arm-linux-g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}.a ${OBJECTS} -c
	rm -f $(OBJECTS)

lib-host:
	g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}host.a ${OBJECTS} -c
	rm -f $(OBJECTS)

target:
	arm-linux-g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}.out main.cpp ${LIBSTARGET} ${LIBS}

host:
	g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}-host.out main.cpp ${LIBSHOST} ${LIBS}

mqread:
	g++ ${CFLAGS} ${LIBPATH} -w -o mqread.out mqread.cpp ${LIBSHOST} ${LIBS}

all:
	#make lib-target
	make lib-host
	#make target
	make host
	make mqread

clean:
	rm -f *.out
	rm -f *.o
	rm -f ../lib/lib${OUTPUT}.a
	rm -f ../lib/lib${OUTPUT}host.a