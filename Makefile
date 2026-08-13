CC=gcc
CFLAGS=-std=c11 -g -Wall

all:
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	rm -rf *.o
