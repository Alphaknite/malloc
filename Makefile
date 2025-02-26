# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -g -Wall -std=c99 -fsanitize=address -fsanitize=undefined

# Targets to build
TARGETS = memgrind mymalloc_myfree_tests memtest

# Source files
SRCS = mymalloc.c memgrind.c memtest.c mymalloc_myfree_tests.c

# Object files
OBJS = mymalloc.o memgrind.o memtest.o mymalloc_myfree_tests.o

# Header files
HEADERS = mymalloc.h

# Default target to build all specified targets
all: $(TARGETS)

# Rule to compile .c files to .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link memgrind executable
memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) -o memgrind memgrind.o mymalloc.o

# Rule to link memtest executable
memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS) -o memtest memtest.o mymalloc.o

# Rule to link mymalloc_myfree_tests executable
mymalloc_myfree_tests: mymalloc_myfree_tests.o mymalloc.o
	$(CC) $(CFLAGS) -o mymalloc_myfree_tests mymalloc_myfree_tests.o mymalloc.o

# Rule to clean up generated files
clean:
	rm -f $(OBJS) $(TARGETS)
