/**
 * @authors Rudra Patel and Aditya Shah
 * @brief My little malloc()
 * @date 2/13/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h";

#define MEM_SIZE 4096; //define the size of memory

/**
 * @struct Metadata struc for memory management
 * 
 * This struc is used to keep track of each memory chunk's status and size.
 * - is_free: A flag indicating whether the chunk is free or allocated.
 * - chunk_length: The size of the memory chunk.
 */
struct meta_data {
    char is_free;
    int chunck_length; 
};



void * mymalloc(size_t size, char *file, int line) {

}

void myfree(void *ptr, char *file, int line) {

}


/**
 * register leak detection function
 * registers the given function as an exit handler
 * when your program exit normally the run-time system will call all exit handlers
 * int atexit(void (*function)(void));
 */


/**
 * called by mymalloc() and myfree() the first time they are called 
 * set up initial state of heap 
 */
static void initialize_heap() {
    //atexit();
    //initialize heap
}

/** 
 * scans heap and prints how many objects are still allocated 
 * intended to run before program exits
 */
static void leak_detector() {

}
