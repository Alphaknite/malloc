#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mymalloc.h"


int test1() {
    for(int i = 0; i < 120; i++) {
        char *ptr = malloc(1);  
        free(ptr);  
    }
}

int test2() {
    char *ptrs[120]; 

    for(int i = 0; i < 120; i++) {
        ptrs[i] = malloc(1);  
        if(ptrs[i] == NULL) {
            fprintf(stderr, "malloc failed in test2\n");
            return EXIT_FAILURE;
        }
    }

    for(int i = 0; i < 120; i++) {
        free(ptrs[i]);  
    }
}

int test3() {
    char *ptrs[120] = {NULL};  
    int allocated = 0;
    srand(time(NULL));

    while(allocated < 120) {
        if(rand() % 2 == 0 && allocated < 120) {
            ptrs[allocated] = malloc(1);
            if(ptrs[allocated] == NULL) {
                fprintf(stderr, "malloc failed in test3\n");
                return EXIT_FAILURE;
            }
            allocated++;
        } else if (allocated > 0) {
            int index = rand() % allocated;
            if(ptrs[index] != NULL) {
                printf("%p\n", ptrs[index]); //debug printf
                free(ptrs[index]);
                ptrs[index] = NULL;  
            }
        }
    }

    for(int i = 0; i < 120; i++) {
        if(ptrs[i] != NULL) {  
            free(ptrs[i]);
            ptrs[i] = NULL;
        }
    }
}


int main() {
    test1();
    test2();
    test3();
    return EXIT_SUCCESS;
}