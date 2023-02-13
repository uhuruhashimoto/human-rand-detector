CC=gcc
CFLAGS=-I. -Wall -pedantic -std=c11 -ggdb 

make: separator truncate

separator: separator.o
	$(CC) -o separator separator.o $(CFLAGS)

truncate: truncate.o
	$(CC) -o truncate truncate.o $(CFLAGS)

clean:
	rm -f separator truncate
	rm -f  *.o
