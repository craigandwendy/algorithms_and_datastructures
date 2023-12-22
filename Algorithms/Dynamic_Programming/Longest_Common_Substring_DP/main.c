#include <stdio.h>
#define P 7
#define Q 8

void init(int M[P+1][Q+1]) {
    int i, j;
    for (i=0;i<P+1;i++) {
        for (j=0;j<Q+1;j++) {
            M[i][j] = 0;
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

int LCS(char A[P], char B[Q], int M[P+1][Q+1]) {
    int i, j;
    int max_i = 0;
    int max_j = 0;
    int lcs = 0;
    init(M);
    for (i=1;i<P+1;i++) {
        for (j=1;j<Q+1;j++) {
            if (A[i] == B[j]) {
                M[i][j] = M[i-1][j-1] + 1;
                max_i = (M[i][j] > M[max_i][max_j]) ? i : max_i;
                max_j = (M[i][j] > M[max_i][max_j]) ? j : max_j;
            }
        }
    }
    lcs = M[max_i][max_j];

    if (!lcs) {
        return 0;
    }

    char temp[lcs];

    while (M[max_i][max_j] > 0) {
        temp[M[max_i][max_j]-1] = A[max_i];
        max_i--;
        max_j--;
    }
    printf("LCS: ");
    for (i=0;i<lcs;i++) {
        printf("%c", temp[i]);
    }
    printf("\n");

    //printMatrix(M);
    return lcs;
}


int main(void) {
    char A[P] = {'b','a','p','f','e','o','d'};
    char B[Q] = {'i','a','p','p','f','e','e','d'};
    int M[P+1][Q+1];
    if (LCS(A,B,M)) {
        printf("Longest common substring found\n");
    } else {
        printf("Longest common substring does not exist\n");
    };
}