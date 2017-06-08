CFLAGS=-O2 -Wall -std=c++11 
CC_TARG=arm-linux-gnueabihf-g++
CC_HOST=g++

lib-host-gcov:	CFLAGS += --coverage
lib-target: CC = $(CC_TARG)
lib-host: 	CC = $(CC_HOST)
target: 	CC = $(CC_TARG)
host: 		CC = $(CC_HOST)

OBJDIR_TARG=obj-target
OBJDIR_HOST=obj-host

SOURCES=Thread.cpp CommunicationServer.cpp MessageQueue.cpp

OBJECTS_TARG=$(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(SOURCES)))
OBJECTS_HOST=$(addprefix $(OBJDIR_HOST)/, $(patsubst %.cpp, %.o, $(SOURCES)))
# $(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

LIBS_TARG=-lcommunication -llogger
LIBS_HOST=-lcommunicationhost -lloggerhost

LIBPATH=-L ../../lib -I ../../lib/include
LIBS=-lstdc++ -lpthread -lrt

OUTPUT=communication

.PHONY: all test clean

lib-host-gcov: lib-host

lib-target: $(OBJDIR_TARG) build-lib-target
lib-host:	$(OBJDIR_HOST) build-lib-host

build-lib-target: $(OBJECTS_TARG)
	cp $(SOURCES:.cpp=.h) ../../lib/include
	ar rvs ../../lib/lib${OUTPUT}.a $^ -c

build-lib-host: $(OBJECTS_HOST)
	cp $(SOURCES:.cpp=.h) ../../lib/include
	ar rvs ../../lib/lib${OUTPUT}host.a $^ -c

target: $(OBJDIR_TARG) build-target
host: 	$(OBJDIR_HOST) build-host

build-target: $(OBJECTS_TARG) $(OBJDIR_TARG)/main.o
	make lib-target
	$(CC) $(CFLAGS) $^ $(LIBPATH) $(LIBS_TARG) $(LIBS) -w -o $(OUTPUT).out

build-host: $(OBJECTS_HOST) $(OBJDIR_HOST)/main.o
	make lib-host
	$(CC) $(CFLAGS) $^ $(LIBPATH) $(LIBS_HOST) $(LIBS) -w -o $(OUTPUT)-host.out

$(OBJDIR_TARG)/%.o: %.cpp
	$(CC) $(CFLAGS) $(LIBPATH) -c $< -o $@

$(OBJDIR_HOST)/%.o: %.cpp
	$(CC) $(CFLAGS) $(LIBPATH) -c $< -o $@

$(OBJDIR_TARG):
	mkdir $(OBJDIR_TARG)

$(OBJDIR_HOST):
	mkdir $(OBJDIR_HOST)

copy:

all:
	make lib-target
	make lib-host
	make target
	make host

clean:
	rm -f *.out
	rm -f *.o
	rm -f ../../lib/lib${OUTPUT}.a
	rm -f ../../lib/lib${OUTPUT}host.a
	rm -f obj-host/*.o
	rm -f obj-target/*.o

test:	
#	cd test && make clean && make test

test-run:
#	cd test && make test-run

test-clean:
#	cd test && make clean
