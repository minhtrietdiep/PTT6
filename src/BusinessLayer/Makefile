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

SOURCES=main.cpp Config.cpp Control.cpp Move.cpp Order.cpp Plate.cpp Preset.cpp
LIBSRCS=Config.cpp Control.cpp Move.cpp Order.cpp Plate.cpp Preset.cpp JSONUtils.cpp

OBJECTS_TARG=$(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(SOURCES)))
OBJECTS_HOST=$(addprefix $(OBJDIR_HOST)/, $(patsubst %.cpp, %.o, $(SOURCES)))
# $(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(wildcard *.cpp)))

LIBSRCS_TARG=$(addprefix $(OBJDIR_TARG)/, $(patsubst %.cpp, %.o, $(LIBSRCS)))
LIBSRCS_HOST=$(addprefix $(OBJDIR_HOST)/, $(patsubst %.cpp, %.o, $(LIBSRCS)))

LIBS_TARG=-lcommunication -llogger -ljsonparser -lhal -lbl
LIBS_HOST=-lcommunicationhost -lloggerhost -ljsonparserhost -lhalhost -lblhost

LIBPATH=-L../lib -I../lib/include -I ../lib/include/rapidjson
LIBS=-lstdc++ -lrt -lpthread

OUTPUT=bl

.PHONY: all test clean

lib-host-gcov: lib-host

lib-target: $(OBJDIR_TARG) build-lib-target
lib-host:	$(OBJDIR_HOST) build-lib-host

build-lib-target: $(LIBSRCS_TARG)
	cp $(LIBSRCS:.cpp=.h) ../lib/include
	ar rvs ../lib/lib${OUTPUT}.a $^ -c
	cp Error.h ../lib/include
	cd Logging; make lib-target

build-lib-host: $(LIBSRCS_HOST)
	cp $(LIBSRCS:.cpp=.h) ../lib/include
	ar rvs ../lib/lib${OUTPUT}host.a $^ -c
	cp Error.h ../lib/include
	cd Logging; make lib-host

copy:
	scp bl.out ptt@192.168.0.10:~

host-gcov: host

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
	cp $(LIBSRCS:.cpp=.h) ../lib/include
	mkdir $(OBJDIR_TARG)

$(OBJDIR_HOST):
	cp $(LIBSRCS:.cpp=.h) ../lib/include
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
	cd test; make clean
	rm -f ../lib/lib${OUTPUT}.a
	rm -f ../lib/lib${OUTPUT}host.a
	rm -f *.out *.o *.gcno *.gcda
	rm -rf obj-host obj-target logs