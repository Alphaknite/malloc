#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mymalloc.h"

#define MEMSIZE 4096
#define HEADERSIZE 8

void test_allocate_memory() {
    void *ptr = malloc(300);
    assert(ptr != NULL);
    printf("Allocated memory sucessfully\n");
    free(ptr);
}

void test_allocate_entire_heap() {
    void *ptr = malloc(MEMSIZE - HEADERSIZE);
    assert(ptr != NULL);
    printf("Allocated the entire heap sucessfully\n");
    free(ptr);
}

void test_allocate_too_much_memory() {
    void *ptr = malloc(6000);
    assert(ptr == NULL);
    printf("Successfully rejected excessive memory request\n");
}

void test_allocate_zero_bytes() {
    void *ptr = malloc(0);
    assert(ptr == NULL);
    printf("Successfully rejected request of zero bytes\n");
}

void test_coalesce() {
    void *ptr1 = malloc(3500);
    void *ptr2 = malloc(174);
    void *ptr3 = malloc(390);
    
    free(ptr2);
    free(ptr3);
    
    void *ptr4 = malloc(572);
    assert(ptr4 != NULL);

    printf("Sucessfully coalesced and allocated new memory block\n");

    free(ptr1);
    free(ptr4);
}

void test_myfree_errors (int case_num) {
    switch (case_num) {
        case 1:
            printf("Test freeing invalid pointer:\n");
            {
                int num = 10;
                void *ptr = &num;
                free(ptr);
            }
            break;

        case 2:
            printf("Test double free:\n");
            {
                void *ptr = malloc(240);
                free(ptr);
                free(ptr);
            }
            break;

        case 3:
            printf("Test freeing null pointer:\n");
            free(NULL);
            break;

        case 4:
            printf("Test freeing a pointer that is not at the beginning of a chunk:\n");
            {
                void *ptr = malloc(500);
                free(ptr + 200);
            }
            break;

        default:
            printf("Case number does not exist\n");
    }

    printf("Should not print this statement\n");
}

int main() {
    test_allocate_memory();
    test_allocate_entire_heap();
    test_allocate_too_much_memory();
    test_allocate_zero_bytes();
    test_coalesce();
    test_myfree(1);
    test_myfree(2);
    test_myfree(3);
    test_myfree(4);
}