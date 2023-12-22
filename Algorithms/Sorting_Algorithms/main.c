#include <stdio.h>
#include <math.h>
#define N 9
/*
 * programme to sort, build and print d-ary heaps*/

int swap(int *a, int *b) { //swaps two elements in an array
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Heapify(int A[], int i, int s, int d) {
    int m = i;
    int l = (i*d) + 1; //find the lower (including) index
    int r = (i*d) + d; //find the upper (including) index
    int j;
    for (j=l;j<=r;j++) {
        if (j<s && A[j] > A[m]) { //A[j] > A[m] --> sorting heap is ascending order A[j] < A[m] --> sorting heap in descending order
            m = j;
        }
    }
    if (i!=m) {
        swap(&A[i], &A[m]);//taking the root of a (sub-)heap and swapping it with the last element
        Heapify(A,m,s,d);
    }
}

void buildMaxHeap(int A[], int n, int d) {
    int i;
    for (i=floor((n)/(d-1));i>=0;i--) {//building heap only until leaves
        Heapify(A,i,n,d);
    }
}

void printHeap(int A[], int n, int d) {
    int i, j;
    for (i=0;i<floor(n/(d-1));i++) {
        for (j=1;j<=d;j++) {
            if ((i*d) + j >= n) {
                break;
            } else {
                printf("%d -- %d\n", A[i], A[(i * d) + j]);
            }
        }
    }
}

void heapSort(int A[], int n, int d) {
    int s = n, i;
    buildMaxHeap(A, s, d);
    for (i=n-1;i>=1;i--) {
        swap(&A[i], &A[0]);//swap A[i] (=biggest/smallest) with A[0]
        s = s-1;
        Heapify(A, 0, s, d);
    }
}

void printArray(int A[], int n) {
    int i;
    for (i=0;i<n;i++) {
        if (i+1==n) {
            printf("%d", A[i]);
        } else {
            printf("%d, ", A[i]);
        }
    }
    printf("\n");
}

int main() {
    int A[N] = {3,1,233,21,0,2,4,50,23};
    heapSort(A,N,2);
    //buildMaxHeap(A,N,2);
    printArray(A,N);
    printHeap(A,N, 2);
    return 0;
}
