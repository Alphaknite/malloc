#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef REALMALLOC
#include "mymalloc.h"
#endif

void test_coalesce() {
    void *ptr1 = mymalloc(3500, __FILE__, __LINE__);
    void *ptr2 = mymalloc(174, __FILE__, __LINE__);
    void *ptr3 = mymalloc(390, __FILE__, __LINE__);
    
    myfree(ptr2, __FILE__, __LINE__);
    myfree(ptr3, __FILE__, __LINE__);
    
    void *ptr4 = mymalloc(572, __FILE__, __LINE__);
    assert(ptr4 != NULL);

    printf("Coalesced and allocated new memory block\n");

    myfree(ptr1, __FILE__, __LINE__);
    myfree(ptr4, __FILE__, __LINE__);
}

void test_myfree (int case_num) {
    switch (case_num) {
        case 1:
            printf("Test freeing valid pointer:\n");
            {
                void *ptr = mymalloc(300, __FILE__, __LINE__);
                myfree(ptr, __FILE__, __LINE__);
            }
            break;
        
        case 2:
            printf("Test freeing invalid pointer:\n");
            {
                int num = 10;
                void *invalid_ptr = &num;
                myfree(invalid_ptr, __FILE__, __LINE__);
            }
            break;

        case 3:
            printf("Test double free:\n");
            {
                void *ptr = mymalloc(240, __FILE__, __LINE__);
                myfree(ptr, __FILE__, __LINE__);
                myfree(ptr, __FILE__, __LINE__);
            }
            break;

        case 4:
            printf("Test freeing null pointer:\n");
            myfree(NULL, __FILE__, __LINE__);
            break;

        case 5:
            printf("Test freeing a pointer that is not at the beginning of a chunk:\n");
            {
                void *ptr = mymalloc(500, __FILE__, __LINE__);
                myfree(ptr + 200, __FILE__, __LINE__);
            }
            break;

        default:
            printf("Case number does not exist\n");
    }

    printf("Only printing this statement if we free a valid pointer\n");
}

int main() {
    test_coalesce();
    test_myfree(2);
    test_myfree(3);
    test_myfree(4);
    test_myfree(5);
}


