CFLAGS=-O2 -Wall -std=c++11
SOURCES=JSONParser.cpp ClientMessage.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../lib/ -I ../lib/
LIBSTARGET=-ljsonparser
LIBSHOST=-ljsonparserhost
OUTPUT=jsonparser
lib-target:
	arm-linux-g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}.a ${OBJECTS} -c
	rm -f $(OBJECTS)
lib-host:
	g++ ${CFLAGS} ${LIBPATH} -c ${SOURCES} ${LIBS}
	ar rvs ../lib/lib${OUTPUT}host.a ${OBJECTS} -c
	rm -f $(OBJECTS)
target:
	arm-linux-g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}.out main.cpp ${LIBS} ${LIBSTARGET}
host:
	g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}-host.out main.cpp ${LIBS} ${LIBSHOST}
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
