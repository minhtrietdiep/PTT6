CC=g++
CFLAGS=-I.
DEPS = socket.h
OBJ = socket.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -lstdc++ -lpthread

hellomake: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) -lstdc++ -lpthread

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm -f hellomake
	rm -f socket.o