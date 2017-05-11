CFLAGS=-O2 -Wall -std=c++11
SOURCES=Thread.cpp CommunicationServer.cpp MessageQueue.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../../lib -I ../../lib/include
LIBS=-lstdc++ -lpthread -lrt
LIBSTARGET=-lcommunication -llogger
LIBSHOST=-lcommunicationhost -lloggerhost
OUTPUT=communication

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

copy:
	scp communication.out ptt@192.168.0.10:~

target:
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}.out main.cpp ${LIBSTARGET} ${LIBS}

host:
	g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}-host.out main.cpp ${LIBSHOST} ${LIBS}

mqread:
	g++ ${CFLAGS} ${LIBPATH} -w -o mqread-host.out mqread.cpp ${LIBSHOST} ${LIBS}
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -w -o mqread.out mqread.cpp ${LIBSTARGET} ${LIBS}

mqsend:
	g++ ${CFLAGS} ${LIBPATH} -w -o mqsend-host.out mqsend.cpp ${LIBSHOST} ${LIBS}
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -w -o mqsend.out mqsend.cpp ${LIBSTARGET} ${LIBS}

test:

all:
	make lib-target
	make lib-host
	make target
	make host
	make mqread
	make mqsend

clean:
	rm -f *.out
	rm -f *.o
	rm -f ../../lib/lib${OUTPUT}.a
	rm -f ../../lib/lib${OUTPUT}host.a
