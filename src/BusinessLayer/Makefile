CC=g++
CFLAGS=-O2 -Wall -std=c++11
TESTLDFLAGS=-lpthread -lgtest -lgtest_main -L/usr/lib -pthread
SOURCES=Config.cpp Control.cpp Move.cpp Order.cpp Plate.cpp Preset.cpp Step.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TESTSOURCES=$(wildcard Tests/*.cpp)
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)
LIBPATH=-L ../lib -I ../lib/include 
LIBS=-lstdc++ -lrt -lpthread
LIBSTARGET=-lcommunication -llogger -ljsonparser
LIBSHOST=-lcommunicationhost -lloggerhost -ljsonparserhost
OUTPUT=bl
TESTEXECUTABLE=Tests/$(OUTPUT)-RunTests.out

lib-target:
	cd Logging; make lib-target

lib-host:
	cd Logging; make lib-host
	

target:
	cd Logging; make target
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}.out ${SOURCES} ${LIBSTARGET} ${LIBS}

host:
	cd Logging; make host
	g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}-host.out ${SOURCES} ${LIBSHOST} ${LIBS}

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TESTSOURCES) $(TESTEXECUTABLE)

$(TESTEXECUTABLE):$(TESTOBJECTS)
	$(CC) $(TESTOBJECTS) $(TESTLDFLAGS)  -o $@

all:
	make lib-target
	make lib-host
	make target
	make host

clean:
	cd Logging; make clean
	rm -f *.out
	rm -f *.o
	$(RM) $(TESTOBJECTS) $(TESTEXECUTABLE)

