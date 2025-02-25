#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mymalloc.h"

void test1() {
    for(int i = 0; i < 120; i++) {
        char *ptr = malloc(1);  
        free(ptr);  
    }
}

void test2() {
    char *ptrs[120]; 

    for(int i = 0; i < 120; i++) {
        ptrs[i] = malloc(1); 
        if(ptrs[i] == NULL) {
            fprintf(stderr, "malloc failed in test2\n");
        }
    }

    for(int i = 0; i < 120; i++) {
        free(ptrs[i]);  
    }
}

void test3() {
    char *ptrArray[120];
    int allocated[120] = {0};  
    int index = 0;

    for(int i = 0; i < 120; i++) {
        if(index == 0 || (rand() % 2 == 0 && index < 120)) {
            printf("allocated index=%d\n", index);
            ptrArray[index] = malloc(1);
            allocated[index] = 1;
            index++;
        } else {
            index--;
            printf("free index=%d\n", index);
            free(ptrArray[index]);
            allocated[index] = 0;
        }
    }

    for(int i = 0; i < 120; i++) {
        if(allocated[i] == 1) {
            free(ptrArray[i]);
        }
    }
}

int main() {
    test1();
    test2();
    test3();
    return EXIT_SUCCESS;
}