CC=gcc
CFLAGS=-I. -Wall -pedantic -std=c11 -ggdb -lcrypto

make: readbits

readbits: readbits.o
	$(CC) -o readbits readbits.o $(CFLAGS)

clean:
	rm -f readbits
	rm -f  *.o
