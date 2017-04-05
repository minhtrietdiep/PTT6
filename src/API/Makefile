CFLAGS=-O2 -Wall
LIBPATH=
SOURCES= socket.cpp
LIBS= -lstdc++ -lpthread

target:
	arm-linux-g++ ${CFLAGS} ${LIBPATH} -w -o socket.out ${SOURCES} ${LIBS} 

host:
	g++ ${CFLAGS} ${LIBPATH} -w -o socket-host.out ${SOURCES} ${LIBS}

all:
	make host
	make target

clean:
	rm -f socket.out
	rm -f socket-host.out