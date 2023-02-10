CC=gcc
CFLAGS=-I. -Wall -pedantic -std=c11 -ggdb -lcrypto

make: readbits randstr strmixer

readbits: readbits.o
	$(CC) -o readbits readbits.o $(CFLAGS)

randstr: randstr.o
	$(CC) -o randstr randstr.o $(CFLAGS)

strmixer: strmixer.o
	$(CC) -o strmixer strmixer.o $(CFLAGS)

clean:
	rm -f readbits strhandler strmixer
	rm -f  *.o
