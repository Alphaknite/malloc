/**
 * @authors Rudra Patel and Aditya Shah
 * @brief My little malloc()
 * @date 2/13/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mymalloc.h"

#define MEMSIZE 4096 //define the size of memory

static void initializeHeap();
static void leakDetector();
static void splitChunk();

/**
 * @struct Metadata struct for memory management
 * this struct is used to keep track of each memory chunk's status and size
 * - is_free: a flag indicating whether the chunk is free or allocated
 * - chunk_length: the size of the memory chunk.
 */
typedef struct {
    int isFree; //1 for free, 0 for allocated
    int chunkLength; 
} MetaData;

static int heapInitialized = 0; //1 for initialized, 0 for uninitialized
static char memory[MEMSIZE];


/**
 * @brief initializes the heap
 * called by mymalloc() and myfree() the first time they are called 
 * set up initial state of heap 
 */
static void initializeHeap() {
    if(heapInitialized == 1) {
        return;
    }

    MetaData *firstChunk = (MetaData *)memory;
    firstChunk->isFree = 1;
    firstChunk->chunkLength = MEMSIZE;

    // atexit(leakDetector); //leak detector function to be written
    heapInitialized = 1;
    printf("Heap Initialized: First chunk size = %d, Free = %d\n", 
            firstChunk->chunkLength, firstChunk->isFree);
    
    //maybe add something for the last block
}

/**
 * @brief finds a free chunk of memory that is large enough to accommodate the request
 * @param size the size of the memory chunk to find
 * @return a pointer to the free chunk, or NULL if no chunk is found
 */
static MetaData *findFreeChunk(size_t size) {
    //start at the beginning of the memory
    MetaData *current = (MetaData *)memory;
    //traverse the heap until we reach the end of memory
    while((char *)current < memory + MEMSIZE) {
        //check if the current chunk is free and large enough to accommodate the request
        if(current->isFree && current->chunkLength >= size) {
            return current;
        }
        //move to the next chunk
        current = (MetaData *)((char *)current + sizeof(MetaData) + current->chunkLength);
    }
    return NULL;
}

/**
 * @brief splits a larger free chunk into 2 smaller chunks
 * @param chunk the chunk to split
 * @param requestedSize the size of the requested size
 */
static void splitChunk(MetaData *chunk, size_t requestedSize) {
    size_t remainingSize = chunk->chunkLength - requestedSize - sizeof(MetaData);

    //marks the new chunk as free and set the remaining size for this new chunk 
    MetaData *newChunk = (MetaData *)((char *)chunk + sizeof(MetaData) + requestedSize);
    newChunk->isFree = 1;
    newChunk->chunkLength = remainingSize;

    //mark the requested size as allocated
    chunk->chunkLength = requestedSize;
    chunk->isFree = 0;
}

/**
 * @brief allocates a block of memory
 * @param size the size of the memory block to allocate
 * @param file the name of the file where the request was made from
 * @param line the line number where the request was made from
 * @return a pointer to the allocated memory block, or NULL if the allocations fails.
 */
void * mymalloc(size_t size, char *file, int line) {
    //initialize the heap if not already
    if(heapInitialized == 0) {
        initializeHeap();
    }

    //check for invalid size requests
    if(size <= 0) {
        fprintf(stderr, "malloc: invalid size (%s:%d)\n", file, line);
        return NULL;
    }
    if (size > MEMSIZE) {
        fprintf(stderr, "malloc: invalid size (%s:%d)\n", file, line);
        return NULL;
    }

    size_t alignedSize = ((size + 7) & ~7); //aligns size to 8 bytes
    if (alignedSize > MEMSIZE) {
        fprintf(stderr, "malloc: requested size exceeds memory limit (%s:%d)\n", file, line);
        return NULL;
    }
    //find a suitable free chunk in the heap that can hold the aligned size.
    MetaData *chunk = findFreeChunk(alignedSize);
    if(chunk == NULL) {
        fprintf(stderr, "malloc: no suitable chunk found (%s:%d)\n", file, line);
        return NULL;
    }
    //if the chunk is larger than required, split it into allocated and free chunks
    if(chunk->chunkLength > alignedSize + sizeof(MetaData)) {
        splitChunk(chunk, alignedSize);
    } 
    else {
        chunk->isFree = 0;
    }

    return (void *)((char *) chunk + sizeof(MetaData));
}

void myfree(void *ptr, char *file, int line) {
    if (ptr == NULL) {
        printf("Invalid pointer (%s:%d)\n", file, line);
        return;
    }
    
    MetaData *chunkToFree = (MetaData *)((char *)ptr - sizeof(MetaData));

    if(chunkToFree->isFree == 1) {
        printf("Error: Freeing deallocated memory (%s:%d)\n", file, line);
        return;
    }
    
    chunkToFree->isFree = 1;

    //Checking if next chunk is free. If free, then merge with freed chunk.
    MetaData *after = (MetaData *)((char *)chunkToFree + sizeof(MetaData) + chunkToFree->chunkLength);
    if (after->isFree && (char *)after < memory + MEMSIZE) {
        chunkToFree->chunkLength = chunkToFree->chunkLength + sizeof(MetaData) + after->chunkLength;
    }
}


static void leakDetector() {
   
}

//THIS IS ALL FOR TESTING, IT CAN BE REMOVED

/**
void test_allocation() {
    printf("Running allocation tests...\n");

    // void *ptr1 = mymalloc(900, __FILE__, __LINE__);
    // void *ptr2 = mymalloc(200, __FILE__, __LINE__);
    void *ptr = mymalloc(4096, __FILE__, __LINE__);
    void *ptr2 = mymalloc(40, __FILE__, __LINE__);


}

void printHeap() {
    MetaData *current = (MetaData *)memory;
    printf("Heap Visualization:\n");
    printf("--------------------------------------------------\n");
    printf("| %-10s | %-10s | %-10s |\n", "Address", "Size", "Status");
    printf("--------------------------------------------------\n");

    while ((char *)current < memory + MEMSIZE) {
        printf("| %-10p | %-10d | %-10s |\n", (void *)current, current->chunkLength, current->isFree ? "Free" : "Allocated");
        current = (MetaData *)((char *)current + sizeof(MetaData) + current->chunkLength);
    }

    printf("--------------------------------------------------\n");
}

int main() {
    test_allocation();
    printHeap();
    return EXIT_SUCCESS;
}
*/