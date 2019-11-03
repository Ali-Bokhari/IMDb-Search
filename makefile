CC = gcc
CFLAGS = -Wall -ansi -pedantic

all: a3

binary.o: common.h binary.c
	$(CC) $(CFLAGS) -c binary.c -o $@

common.o: common.c
	$(CC) $(CFLAGS) -c common.c -o $@

name.o: binary.h common.h name.c
	$(CC) $(CFLAGS) -c name.c -o $@

title.o: binary.h common.h title.c
	$(CC) $(CFLAGS) -c title.c -o $@

principles.o: binary.h common.h principles.c
	$(CC) $(CFLAGS) -c principles.c -o $@

a3.o: *.h a3.c
	$(CC) $(CFLAGS) -c a3.c -o $@

a3: a3.o principals.o title.o name.o binary.o common.o
	$(CC) $^ -o $@

clean:
	rm *.o
