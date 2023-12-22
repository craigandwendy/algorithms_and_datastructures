#include <stdio.h>
#include <math.h>
#define N 20



void Merge(int Arr[], int l, int r, int m) {
    int i, j;
    int B[N] = {};

    for (i=l;i<m+1;i++) { //i < m+1 because we want to fill in until m incl. m
        B[i] = Arr[i];
    }
    for (i=m+1;i<=r;i++) { //i <= r because r = N - 1
        B[r+m-i+1] = Arr[i]; //sort second half in reverse order
    }
    i = l;
    j = r;
    int k;
    for (k=l;k<=r;k++) { //k <= r because r = N - 1
        if (B[i] < B[j]) {
            Arr[k] = B[i];
            i = i + 1;
        } else {
            Arr[k] = B[j];
            j = j - 1;
        }
    }
}

void MergeSort(int Arr[], int l, int r) {
    if (l < r) {
        int m = floor((l+r)/2);
        MergeSort(Arr, l, m);
        MergeSort(Arr, m+1, r);
        Merge(Arr, l, r, m);
    }
}


int main() {
    int Arr[N] = {5, 3, 8, 0,13, 10, 4, 7, 9, 2, 19, 31, 15, 6, 1, 12, 33, 11, 23, 16};
    //int Arr[N] = {3, 7, 9, 1, 0, 2, 5, 6};
    int l = 0;
    int r = N - 1;
    MergeSort(Arr, l, r);
    int i;
    for (i=0;i<N;i++) {
        if (i+1==N) {
            printf("%d", Arr[i]);
        } else {
            printf("%d - ", Arr[i]);
        }
    }
    return 0;
}
