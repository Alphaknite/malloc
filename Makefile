CC = gcc
CFLAGS = -g -Wall -std=c99 -fsanitize=address -fsanitize=undefined

TARGETS = memgrind mymalloc mymalloc_myfree_tests memtest

SRCS = mymalloc.c memgrind.c memtest.c mymalloc_myfree_tests.c
OBJS = mymalloc.o

HEADERS = mymalloc.h

all: $(TARGETS)

mymalloc.o: mymalloc.c $(HEADERS)
	$(CC) $(CFLAGS) -c mymalloc.c

memgrind: memgrind.c mymalloc.o
	$(CC) $(CFLAGS) -o memgrind memgrind.c mymalloc.o

memtest: memtest.c mymalloc.o
	$(CC) $(CFLAGS) -o memtest memtest.c mymalloc.o

mymalloc_myfree_tests: mymalloc_myfree_tests.c mymalloc.o
	$(CC) $(CFLAGS) -o mymalloc_myfree_tests mymalloc_myfree_tests.c mymalloc.o

clean:
	rm -f $(OBJS) $(TARGETS)