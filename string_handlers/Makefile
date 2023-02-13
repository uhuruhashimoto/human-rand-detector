CC=gcc
CFLAGS=-I. -Wall -pedantic -std=c11 -ggdb -lcrypto

make: randstr strmixer

randstr: randstr.o
	$(CC) -o randstr randstr.o $(CFLAGS)

strmixer: strmixer.o
	$(CC) -o strmixer strmixer.o $(CFLAGS)

clean:
	rm -f strhandler strmixer
	rm -f  *.o
