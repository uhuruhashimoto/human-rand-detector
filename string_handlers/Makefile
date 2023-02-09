CC=gcc
CFLAGS=-I. -Wall -pedantic -std=c11 -ggdb 

make: rc4demo desW23

rc4demo: rc4demo.o 
	$(CC) -o rc4demo rc4demo.o $(CFLAGS) 

desW23: desW23.o
	$(CC) -o desW23 desW23.o $(CFLAGS) -lcrypto

clean:
	rm -f rc4demo desW23
	rm -f  *.o
