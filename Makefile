CC = gcc
CFLAGS = -g -Wall -std=c99 -fsanitize=address -fsanitize=undefined

TARGETS = memgrind mymalloc_myfree_tests memtest

SRCS = mymalloc.c memgrind.c memtest.c mymalloc_myfree_tests.c
OBJS = mymalloc.o memgrind.o memtest.o mymalloc_myfree_tests.o

HEADERS = mymalloc.h

all: $(TARGETS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) -o memgrind memgrind.o mymalloc.o

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS) -o memtest memtest.o mymalloc.o

mymalloc_myfree_tests: mymalloc_myfree_tests.o mymalloc.o
	$(CC) $(CFLAGS) -o mymalloc_myfree_tests mymalloc_myfree_tests.o mymalloc.o

clean:
	rm -f $(OBJS) $(TARGETS)
