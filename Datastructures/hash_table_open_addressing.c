#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M 5
#define OCC 0
#define EMP -1
#define DEL -2


struct elem {
    int key;
    int status; //0 = occupied, -1 = empty, -2 = deleted
};

void init(struct elem A[]) {
    int i;
    for (i=0;i<M;i++) {
        A[i].status = EMP;
    }
}

int hash(int k, int i) {
    return (k+i)%M;
}

int insert(struct elem A[], int k) {
    int i = 0;
    int pos;
    do {
        pos = hash(k,i);
        i++;
    } while (i<=M && A[pos].status != EMP);
    A[pos].key = k;
    A[pos].status = OCC;
    return pos;
}

int search(struct elem A[], int k) {
    int i = 0;
    int pos;
    do {
        pos = hash(k,i);
        i++;
    } while (i<=M && (A[pos].status != OCC || A[pos].key != k) && A[pos].status != EMP);
    if (i >= M || A[pos].key == EMP) {
        return -1;
    }
    return pos;
}

int delete(struct elem A[], int k) {
    int i = 0;
    int pos;
    do {
        pos = hash(k,i);
        i++;
    } while (i<=M && (A[pos].status != OCC || A[pos].key != k) && A[pos].status != EMP);
    if (i >= M || A[pos].key == EMP) { //when A[pos].key != k is missing, deletion has some mistakes --> check delete(A, 26)
        return -1;
    }
    A[pos].status = DEL;
    return pos;
}

void printHT(struct elem A[]) {
    int i;
    printf("Ind | Stat | Key\n");
    for (i=0;i<M;i++) {
        printf(" %d  |  %d   | %d\n", i, A[i].status, A[i].key);
    }
    printf("\n\n");
}

int main(void) {
    struct elem A[M];
    int i;
    init(A);
    for (i=1;i<=3;i++) {
        insert(A, 5*i);
    }
    printHT(A);
    delete(A, 5);
    printHT(A);
    delete(A, 124523);
    printHT(A);
}
