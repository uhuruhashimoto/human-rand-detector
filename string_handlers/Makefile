CC=gcc
CFLAGS=-I. -Wall -pedantic -std=c11 -ggdb -lcrypto

make: readbits strhandler

readbits: readbits.o
	$(CC) -o readbits readbits.o $(CFLAGS)

strhandler: strhandler.o
	$(CC) -o strhandler strhandler.o $(CFLAGS)

clean:
	rm -f readbits strhandler
	rm -f  *.o
