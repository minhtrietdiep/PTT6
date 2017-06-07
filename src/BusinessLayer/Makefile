CFLAGS=-O2 -Wall -std=c++11
CC_TARG=arm-linux-gnueabihf-g++
CC_HOST=g++

target: CC = $(CC_TARG)
host: 	CC = $(CC_HOST)

OBJDIR_TARG=obj-target
OBJDIR_HOST=obj-host

SOURCES=main.cpp Config.cpp Control.cpp Move.cpp Order.cpp Plate.cpp Preset.cpp

OBJECTS_TARG=$(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(SOURCES)))
OBJECTS_HOST=$(addprefix $(OBJDIR_HOST)/, $(patsubst %.cpp, %.o, $(SOURCES)))
# $(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

LIBS_TARG=-lcommunication -llogger -ljsonparser -lhal
LIBS_HOST=-lcommunicationhost -lloggerhost -ljsonparserhost -lhalhost

LIBPATH=-L../lib -I../lib/include -I ../lib/include/rapidjson
LIBS=-lstdc++ -lrt -lpthread

OUTPUT=bl

.PHONY: all test clean

lib-target:
	cp Error.h ../lib/include
	cd Logging; make lib-target

lib-host:
	cp Error.h ../lib/include
	cd Logging; make lib-host
	
copy:
	scp bl.out ptt@192.168.0.10:~

target: $(OBJDIR_TARG) build-target
host: 	$(OBJDIR_HOST) build-host

build-target: $(OBJECTS_TARG)
	make lib-target
	$(CC) $(CFLAGS) $^ $(LIBPATH) $(LIBS_TARG) $(LIBS) -w -o $(OUTPUT).out

build-host: $(OBJECTS_HOST)
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

test:
	cd test && make test

test-run:
	cd test && make test-run

test-clean:
	cd test && make clean
	
all:
	make lib-target
	make lib-host
	make target
	make host
	make test

clean:
	cd Logging; make clean
	rm -f *.out
	rm -f *.o
	rm -f *.gcno
	rm -f *.gcda
	rm -f obj-host/*.o
	rm -f obj-target/*.o
	$(RM) $(TESTOBJECTS) $(TESTEXECUTABLE)

