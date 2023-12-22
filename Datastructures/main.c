#include <stdio.h>
#include <stdlib.h>
#define N 9
int SIZE = N;
/* program with the most important functions on linked lists
 * definition of a linked list
 * first element is called root, it is a pointer that points on the first value/element of the linked list
 * the last element always points NULL meaning last->next = NULL
 * the elements of a singly linked list contain a value and a pointer (address) to the next element
 *
 * 03x40f       04x05a           06x91c
 * |------|    |-----------|    |-----------|
 * |04x05a|--->| 55 |06x91c|--->| 23 | NULL |
 * |------|    |-----------|    |-----------|
 *
 * */

struct Node {
    int val;
    struct Node *next;
};

/*struct Node *convert(int *A, int n) {
    //converting an array to a linked list: A = {3, 5, 1, 9}
    // root-->3-->5-->1-->9

    struct Node *root = NULL; //pointer to first element
    struct Node *last = NULL; //pointer pointing on last element
    struct Node *p; //pointer used to allocate memory and insert values in linked list
    int i;
    for (i=0;i<n;i++) {
        p = malloc(sizeof(struct Node)); //create memory space in heap for an element
        p->val = *A; //p is pointing to a struct which has a value
        p->next = NULL; //and the pointer (address) to the next element
        if (i==0) { //special case, when there is no element in the linked list root=p
            root = last = p;
        } else { //if there is 1 or more element we just insert at the last position instead of traversing O(n)
            last->next = p; //the previous element (last) has next = p
            last = p; //the new inserted element is now the last element
        }
        A++; //increase array pointer by one, allowed because array is continuous in memory
    }

    return root; //return the root
}
*/

void ConvertArrToLL(struct Node **root, int A[], int n) {
    struct Node *last = NULL;
    struct Node *p;
    int i;
    for (i=0;i<n;i++) {
        p = malloc(sizeof(struct Node));
        p->val = *A;
        p->next = NULL;
        if (i==0) {
            *root = last = p;
        } else {
            last->next = p;
            last = p;
        }
        A++;
    }
}

void InsertAtPosition(struct Node **root, int v, int pos) { //inserting an element at any specific position in a linked list
    struct Node *t = *root;
    struct Node *p;
    p = malloc(sizeof(struct Node));
    p->val = v;
    p->next = NULL;
    int i;
    for (i=0;i<pos-1;i++) {
        t = t->next;
    }
    if (pos==0) {
        p->next = (*root);
        *root = p;
    } else {
        p->next = t->next;
        t->next = p;
    }
    SIZE++;
}

void InsertFirst(struct Node **root, int v) {
    struct Node *p;
    p = malloc(sizeof(struct Node));
    p->val = v;
    p->next = *root;
    *root = p;
    SIZE++;
}

void InsertLast(struct Node **root, int v) {
    struct Node *t = *root;
    struct Node * p;
    while (t->next) {
        t = t->next;
    }
    p = malloc(sizeof(struct Node));
    p->val = v;
    p->next = NULL;
    t->next = p;
    SIZE++;
}

void RemoveAtPosition(struct Node **root, int pos) {
    struct Node *t = *root;
    struct Node *p = t->next; //to avoid memory leak, need to create a second pointer
    int i;
    for (i=0;i<pos-1;i++){
        t = t->next;
        p = p->next;
    }
    if (pos == 0) {
        t = (*root)->next;
        free(*root);
        *root = t;
    } else {
        t->next = p->next; //t->next is set to p->next
        free(p); //remove p
    }
    SIZE--;
}

void RemoveLast(struct Node **root) {
    struct Node *t = *root;
    struct Node *p = t->next;
    while (t->next->next) {
        t = t->next;
        p = p->next;
    }
    t->next = NULL;
    free(p);
    SIZE--;
}

void RemoveFirst(struct Node **root) {
    struct Node *t = *root;
    t = t->next;
    free(*root);
    *root = t;
    SIZE--;
}

void Show(struct Node *root) {
    struct Node *p = root;
    while (p) {
        printf("%d\n",p->val);
        p = p->next;
    }
}

int main(void) {
    int A[N] = {9, 3, 5, 1, 0, 2, 8, 4, 7};
    struct Node *root = NULL;
    ConvertArrToLL(&root,A,N);
    InsertAtPosition(&root,99, 9);
    InsertAtPosition(&root,100, 10);
    RemoveAtPosition(&root, 3);
    RemoveLast(&root);
    RemoveFirst(&root);
    InsertFirst(&root, 1);
    InsertLast(&root, 100);
    //struct Node *root = convert(A,N);
    Show(root);
    printf("Size = %d", SIZE);
}