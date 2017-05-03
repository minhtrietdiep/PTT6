CFLAGS=-O2 -Wall -std=c++11
GFLAGS=-O0 -Wall -std=c++11 -g
SOURCES=
#Config.cpp Control.cpp Move.cpp Order.cpp Plate.cpp Preset.cpp Step.cpp BL.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBPATH=-L ../lib -I ../lib/include 
LIBS=-lstdc++ -lrt -lpthread
LIBSTARGET=-lcommunication -llogger -ljsonparser
LIBSHOST=-lcommunicationhost -lloggerhost -ljsonparserhost
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
host-g:
	cd Logging; make host
	g++ ${GFLAGS} ${LIBPATH} -w -o $(OUTPUT)-host.out main.cpp ${LIBSHOST} ${LIBS}

test:

all:
	make lib-target
	make lib-host
	make target
	make host

clean:
	cd Logging; make clean
	rm -f *.out
	rm -f *.o
