#include <stdio.h>
#define N 8
#define Q 8

void init(int M[N+1][Q+1]) {
    int i,j;
    for (i=0;i<N+1;i++) {
        for (j=0;j<Q+1;j++) {
            M[i][j] = 0;
        }
    }
}

void printMatrix(int M[N+1][Q+1]) {
    int i,j;
    for (i=1;i<N+1;i++) {
        for (j=1;j<Q+1;j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int lcs(char A[N], char B[Q], int M[N+1][Q+1]) {
    init(M);
    int i, j;
    for (i=0;i<N;i++) {
        for (j=0;j<Q;j++) {
            if (A[i] == B[j]) {
                M[i+1][j+1] = M[i][j] + 1;
            } else if (M[i+1-1][j+1] >= M[i+1][j+1-1]) {
                M[i+1][j+1] = M[i+1-1][j+1];
            } else {
                M[i+1][j+1] = M[i+1][j+1-1];
            }
        }
    }

    printMatrix(M);

    return M[N][Q];
}


int main(void) {
    char A[N] = {'a','b','d','e','f','f','c','b'};
    char B[Q] = {'a','b','d','a','c','c','f','a'};
    int M[N+1][Q+1];
    printf("\n\nLongest Common Subsequence = %d\n\n", lcs(A,B,M));
}