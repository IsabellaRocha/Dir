ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: dirinfo.o
	$(CC) -o program dirinfo.o

dirinfo.o: dirinfo.c
	$(CC) -c dirinfo.c

run:
	./program
