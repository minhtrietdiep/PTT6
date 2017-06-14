CFLAGS=-O2 -Wall -std=c++11
CC_TARG=arm-linux-gnueabihf-g++
CC_HOST=g++

lib-host-gcov:	CFLAGS += --coverage
host-gcov:		CFLAGS += --coverage
lib-target: CC = $(CC_TARG)
lib-host: 	CC = $(CC_HOST)
target: 	CC = $(CC_TARG)
host: 		CC = $(CC_HOST)

OBJDIR_TARG=obj-target
OBJDIR_HOST=obj-host

SOURCES=Arm.cpp Drive.cpp Vacuum.cpp HAL.cpp

OBJECTS_TARG=$(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(SOURCES)))
OBJECTS_HOST=$(addprefix $(OBJDIR_HOST)/, $(patsubst %.cpp, %.o, $(SOURCES)))
# $(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

LIBS_TARG=-lhal -llogger
LIBS_HOST=-lhalhost -lloggerhost

LIBPATH=-L ../lib -I ../lib/include
LIBS=-lpthread -lrt

OUTPUT=hal

.PHONY: all test clean

lib-host-gcov: lib-host

lib-target: $(OBJDIR_TARG) build-lib-target
lib-host:	$(OBJDIR_HOST) build-lib-host

build-lib-target: $(OBJECTS_TARG)
	cp $(SOURCES:.cpp=.h) ../lib/include
	ar rvs ../lib/lib${OUTPUT}.a $^ -c

build-lib-host: $(OBJECTS_HOST)
	cp $(SOURCES:.cpp=.h) ../lib/include
	ar rvs ../lib/lib${OUTPUT}host.a $^ -c

host-gcov: host

target:

host:

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
	cd test; make clean
	rm -f ../lib/lib${OUTPUT}.a
	rm -f ../lib/lib${OUTPUT}host.a
	rm -f *.out *.o *.gcno *.gcda
	rm -rf obj-host obj-target logs
	
test:	
	cd test && make test
test-run:
	cd test && make test-run
test-clean:
	cd test && make clean
