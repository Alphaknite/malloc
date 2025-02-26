#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mymalloc.h"

//  Test 1
//-----------------------------------------------------------------------------
/**
 * @brief test allocating and freeing 1 byte of memory 120 times
 */
void test1() {
    for(int i = 0; i < 120; i++) {
        char *ptr = malloc(1);
        free(ptr);
    }
}

//  Test 2
//-----------------------------------------------------------------------------
/**
 * @brief test allocating and freeing 1 byte of memory 120 times using an array
 */
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

//  Test 3
//-----------------------------------------------------------------------------
/**
 * @brief test allocating and freeing 1 byte of memory 120 times with random 
 *        allocation and deallocation
 */
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
        }
        else {
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

//  Test 4
//-----------------------------------------------------------------------------
/**
 * @brief test allocating and freeing a linked list of 120 nodes
 */
typedef struct node {
    char data;
    struct node *next;
} node_t;

void test4() {
    
    node_t *head = NULL;

    for(int i = 0; i < 120; i++) {
        node_t *newNode = (node_t *)malloc(sizeof(node_t));
        newNode->data = 'A' + i % 26;
        newNode->next = head;
        head = newNode;
    }

    // Print Linked List
    printf("Linked List: ");
    node_t *current = head;
    while(current != NULL) {
        printf("%c -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    while(head) {
        node_t *temp = head;
        head = head->next;
        free(temp);
    }

    // Print Linked List
    printf("Linked List: ");
    node_t *curr = head;
    while(curr != NULL) {
        printf("%c -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

//  Test 5
//-----------------------------------------------------------------------------
/**
 * @brief test allocating and freeing a binary tree of 120 nodes
 */
typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/**
 * @brief Insert a node into the binary tree
 * @param root The root of the tree
 * @param data The data to insert
 * @return The new root of the tree
 */
TreeNode* insertNode(TreeNode *root, char data) {
    if(root == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        if(newNode == NULL) {
            fprintf(stderr, "malloc failed in insertNode\n");
            return NULL;
        }
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if(data < root->data) root->left = insertNode(root->left, data);
    else root->right = insertNode(root->right, data);
    return root;
}

void freeTree(TreeNode *root) {
    if(root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void test5() {
    TreeNode *root = NULL;
    
    // Insert nodes
    for(int i = 0; i < 120; i++) {
        root = insertNode(root, 'A' + (i % 26));
    }

    // Free tree
    freeTree(root);

    printf("Tree freed\n");
}

//  Main
//-----------------------------------------------------------------------------
int main() {
    struct timeval start;
    struct timeval end;
    double elapsed;
    double average;

    gettimeofday(&start, NULL);

    for(int i = 0; i < 50; i++){
        test1();
        test2();
        test3();
        test4();
        test5();
    }
    
    gettimeofday(&end, NULL);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    average = elapsed / 50;

    printf("Average time per run: %f seconds\n", average);
    return EXIT_SUCCESS;
}