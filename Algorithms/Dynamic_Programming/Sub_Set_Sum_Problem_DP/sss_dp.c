#include <stdio.h>
#define N 4
#define SUM 11

void init(int M[N][SUM+1]) {
    int i, j;
    for (i=0;i<N;i++) {
        for (j=0;j<SUM+1;j++) {
            if (j==0) {
                M[i][j] = 1;
            } else {
                M[i][j] = 0;
            }
        }
    }
}

void printMatrix(int M[N][SUM+1]) {
    int i, j;
    for (i=0;i<N;i++) {
        for (j=0;j<SUM+1;j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

void getSet(int A[N], int M[N][SUM+1]) {
    int i = N;
    int j = SUM;
    while (j > 0) {
        if (M[i-1][j] == 0) {
            printf("%d, ", A[i]);
            j = j - A[i];
            i--;
        }
        if (M[i-1][j] == 1) {
            i--;
        }
    }
    printf("\n");
}

int SSS(int A[N], int M[N][SUM+1]) {
    int i, j;
    init(M);
    for (i=0;i<N;i++) {
        for (j=1;j<SUM+1;j++) {
            if (i==0) {
                if (A[i] == j) {
                    M[i][j] = 1;
                } else {
                    M[i][j] = 0;
                }
            } else {
                if (A[i] > j) {
                    M[i][j] = M[i-1][j];
                } else {
                    M[i][j] = M[i-1][j] || M[i-1][j-A[i]];
                }
            }
        }
    }
    return M[N-1][SUM];
}


int main(void) {
    int A[N] = {2,3,7,8};
    int M[N][SUM+1];
    if (SSS(A, M) == 1) {
        printf("Subset found!\n");
        getSet(A,M);
    } else {
        printf("Subset not found!\n");
    }
}
