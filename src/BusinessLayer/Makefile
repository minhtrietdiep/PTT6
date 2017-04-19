CFLAGS=-O2 -Wall -std=c++11
SOURCES=Config.cpp Control.cpp Move.cpp Order.cpp Plate.cpp Preset.cpp Step.cpp BL.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../lib -I ../lib/include
LIBS=-lstdc++
LIBSTARGET=-lcommunication -llogger
LIBSHOST=-lcommunicationhost -lloggerhost
OUTPUT=bl

lib-target:
	cd Logging; make lib-target

lib-host:
	cd Logging; make lib-host
	

target:
	cd Logging; make target
	arm-linux-gnueabihf-g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}.out main.cpp ${LIBSTARGET} ${LIBS}

host:
	cd Logging; make host
	g++ ${CFLAGS} ${LIBPATH} -w -o ${OUTPUT}-host.out main.cpp ${LIBSHOST} ${LIBS}

test:

all:
	cd Logging; make all
	make lib-target
	make lib-host
	make target
	make host
	make test
	

clean:
	cd Logging; make clean
	rm -f *.out
	rm -f *.o
	