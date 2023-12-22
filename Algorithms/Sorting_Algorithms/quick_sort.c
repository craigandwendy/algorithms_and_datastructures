#include <stdio.h>
#define N 8
#define TRUE 1

void printArray(int A[], n) {
    int i;
    for (i=0;i<n;i++) {
        if (i+1==n) {
            printf("%d", A[i]);
        } else {
            printf("%d, ", A[i]);
        }
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int HoarePartition(int A[], int l, int r);

void QuickSort(int A[], int l, int r) {
    if (l<r) {
        int m = HoarePartition(A,l,r);
        QuickSort(A,l,m-1);
        QuickSort(A,m,r);
    }
}

int HoarePartition(int A[], int l, int r) {
    int x = A[r], i = l-1, j = r+1;
    while (TRUE) {
        do {
            j--;
        }
        while (A[j] > x);

        do {
            i++;
        }
        while (A[i] < x);

        if (i < j) {
            swap(&A[i], &A[j]);
        } else {
            return i;
        }
    }
}


int main(void) {
    int A[N] = {5, 3, 9, 1, 0, 2, 8, 4};
    QuickSort(A,0,N-1); //use N-1 because j = r + 1 in HoarePartition()!!! N works too, but might cause index mistakes
    printArray(A, N);
    return 0;
}
