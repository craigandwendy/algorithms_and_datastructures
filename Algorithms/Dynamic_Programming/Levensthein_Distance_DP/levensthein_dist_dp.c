#include <stdio.h>
#define P 5
#define Q 6

void init(int M[P+1][Q+1]) {
    int i, j;
    for (i=0;i<P+1;i++) {
        for (j=0;j<Q+1;j++) {
            if (i==0) {
                M[i][j] = j;
            } else if (j==0) {
                M[i][j] = i;
            } else {
                M[i][j] = 0;
            }
        }
    }
}

void printMatrix(int M[P+1][Q+1]) {
    int i, j;
    for (i=0;i<P+1;i++) {
        for (j=0;j<Q+1;j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int min(int A, int B, int C) {
    if (A < B && A < C) {
        return A;
    }
    if (B < C && B < A) {
        return B;
    }
    return C;
}

int levensthein(char A[P], char B[Q], int M[P+1][Q+1]) {
    int i, j;
    init(M);
    for (i=1;i<P+1;i++) {
        for (j=1;j<Q+1;j++) {
            if (A[i-1] == B[j-1]) {
                M[i][j] = M[i-1][j-1];
            } else {
                M[i][j] = min(M[i-1][j-1], M[i][j-1], M[i-1][j]) + 1;
            }
        }
    }

    printMatrix(M);

    return M[P][Q];
}

int main(void) {
    int M[P+1][Q+1];
    char A[P] = {'t','u','n','d','r'};
    char B[Q] = {'h','o','n','d','e','r'};
    printf("\n\nLevensthein distance = %d\n\n", levensthein(A,B,M));
}
