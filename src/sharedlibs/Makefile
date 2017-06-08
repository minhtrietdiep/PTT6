CFLAGS=-O2 -Wall -std=c++11
CC_TARG=arm-linux-gnueabihf-g++
CC_HOST=g++

lib-target: CC = $(CC_TARG)
lib-host: 	CC = $(CC_HOST)
target: CC = $(CC_TARG)
host: 	CC = $(CC_HOST)

OBJDIR_TARG=obj-target
OBJDIR_HOST=obj-host

SOURCES=JSONParser.cpp ClientMessage.cpp

OBJECTS_TARG=$(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(SOURCES)))
OBJECTS_HOST=$(addprefix $(OBJDIR_HOST)/, $(patsubst %.cpp, %.o, $(SOURCES)))
# $(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

LIBS_TARG=-ljsonparser
LIBS_HOST=-ljsonparserhost

LIBPATH=-L ../lib -I ../lib/include
LIBS=

OUTPUT=jsonparser

.PHONY: all test clean

lib-target: $(OBJDIR_TARG) build-lib-target
lib-host:	$(OBJDIR_HOST) build-lib-host

build-lib-target: $(OBJECTS_TARG)
	cp JSONError.h ../lib/include
	cp $(SOURCES:.cpp=.h) ../lib/include
	ar rvs ../lib/lib${OUTPUT}.a $^ -c

build-lib-host: $(OBJECTS_HOST)
	cp JSONError.h ../lib/include
	cp $(SOURCES:.cpp=.h) ../lib/include
	ar rvs ../lib/lib${OUTPUT}host.a $^ -c

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
	rm -f *.out
	rm -f *.o
	rm -f ../lib/lib${OUTPUT}.a
	rm -f ../lib/lib${OUTPUT}host.a
	rm -f obj-host/*.o
	rm -f obj-target/*.o
	
test:	
	cd test && make test
test-run:
	cd test && make test-run
test-clean:
	cd test && make clean
