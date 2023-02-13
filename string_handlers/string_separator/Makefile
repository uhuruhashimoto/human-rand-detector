CC=gcc
CFLAGS=-I. -Wall -pedantic -std=c11 -ggdb 

make: separator 

separator: separator.o
	$(CC) -o separator separator.o $(CFLAGS)

clean:
	rm -f hashtime
	rm -f  *.o
