#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M 5

struct node{
    int key;
    struct node *next;
};

void init(struct node *HT[]) {
    int i;
    for (i=0;i<M;i++) {
        HT[i] = NULL;
    }
}

int hash(int k) {
    int i = rand() %M;
    return k%M;
}

int search(struct node *HT[], int k) {
    int pos = hash(k);
    struct node *t = HT[pos];
    while (t) {
        if (t->key == k) {
            return 1;
        }
        t = t->next;
    }
    return -1;
}

void delete(struct node *HT[], int k) {
    if (search(HT, k) == -1) {
        printf("\nElement %d is not in hash table!\n", k);
        return;
    }
    int pos = hash(k);
    struct node *t = HT[pos];
    struct node *l = NULL;
    while (t->key != k) {
        l = t;
        t = t->next;
    }
    if (l == NULL) { //element is at root;
        HT[pos] = HT[pos]->next;
        free(t);
        printf("\nElement %d was successfully deleted from index %d.\n", k, pos);
        return;
    } //element is not at root
    l->next = t->next;
    free(t);
    printf("\nElement %d was successfully deleted from index %d.\n", k, pos);
}

void insert(struct node *HT[], int k) {
    int pos = hash(k);
    struct node *t = HT[pos];
    struct node *p = malloc(sizeof(struct node));
    p->key = k;
    p->next = NULL;
    if (!t) {
        HT[pos] = p;
        return;
    }
    HT[pos] = p;
    HT[pos]->next = t;
}

void printHT(struct node *HT[]) {
    int i;
    struct node *t;
    printf(" Ind\n");
    for (i=0;i<M;i++) {
        printf(" ———\n");
        printf("| %d | ", i);
        t = HT[i];
        while (t) {
            printf("%d --> ", t->key);
            t = t->next;
        }
        printf("NULL\n");
    }
    printf(" ———\n");
}

int main(void) {
    struct node *HT[M];
    init(HT);
    int i;
    for (i=0;i<10;i++) {
        insert(HT, rand() % 10);
    }
    printHT(HT);
}