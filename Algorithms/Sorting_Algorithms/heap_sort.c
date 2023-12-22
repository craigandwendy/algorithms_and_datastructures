#include <stdio.h>
#include <math.h>
#define N 8
//heap sort for binary trees

void printArray(int A[]) {
    int i;
    for (i=0;i<N;i++) {
        if (i+1 == N) {
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

int Parent(int i) {
    return floor(i/2);
}

int Left(int i) {
    return (2*i)+1; //formula d-ary heaps--> (d*i)+1
}

int Right(int i) {
    return (2*i)+2; //formula d-ary heaps--> (d*i)+d
}

void Heapify(int A[], int i, int s) { //max-heap--> biggest element in the top, runtime log(n)
    int m = i;
    int l = Left(i);
    int r = Right(i);
    if (l<=s && A[l]>A[m]) {
        m = l;
    }
    if (r<=s && A[r]>A[m]) {
        m = r;
    }
    if (i!=m) {
        swap(&A[i], &A[m]);
        Heapify(A,m,s);
    }
}

void BuildHeap(int A[], int n) {
    int i;
    for (i=floor(n/2);i>=0;i--) {
        Heapify(A,i,n);
    }
}

void Heapsort(int A[], int n) { //call n-1 times heapify and swap top element with last element, O(n log(n))
    int s = n;
    BuildHeap(A, n);
    int i;
    for (i=n;i>0;i--) { //O(n)
        swap(&A[i], &A[0]); //O(1)
        s = s-1; //O(1)
        Heapify(A,0,s); //O(log(n)
    }
}

int main(void) {
    int A[N] = {3, 6, 2, 9, 0, 4, 1, 7};
    Heapsort(A, N-1);
    printArray(A);
    return 0;
}
