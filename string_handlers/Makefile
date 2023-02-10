CC=gcc
CFLAGS=-I. -Wall -pedantic -std=c11 -ggdb -lcrypto

make: readbits strhandler strmixer

readbits: readbits.o
	$(CC) -o readbits readbits.o $(CFLAGS)

strhandler: strhandler.o
	$(CC) -o strhandler strhandler.o $(CFLAGS)

strmixer: strmixer.o
	$(CC) -o strmixer strmixer.o $(CFLAGS)

clean:
	rm -f readbits strhandler strmixer
	rm -f  *.o
