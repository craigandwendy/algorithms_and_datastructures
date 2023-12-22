#include <stdio.h>
#define N 6
#define MAX_W 10

void init(int M[N+1][MAX_W+1]) {
    int i,j;
    for (i=0;i<N+1;i++) {
        for (j=0;j<MAX_W+1;j++) {
            M[i][j] = 0;
        }
    }
}

void printMatrix(int M[N+1][MAX_W+1]) {
    int i, j;
    for (i=1;i<N+1;i++) {
        for (j=1;j<MAX_W+1;j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

int max(int A, int B) {
    return (A>B) ? A:B;
}

int knapsack(int W[N], int V[N], int M[N+1][MAX_W+1]) {
    int i, j;
    init(M);

    for (i=1;i<N+1;i++) {
        for (j=0;j<MAX_W+1;j++) {
            if (W[i-1] > j) {
                M[i][j] = M[i-1][j];
            } else {
                M[i][j] = max(M[i-1][j], M[i-1][j-W[i-1]] + V[i-1]);
            }
        }
    }

    printMatrix(M);

    return M[N][MAX_W];
}

int main(void) {
    int W[N] = {1,2,3,4,7,8};
    int V[N] = {20,5,10,25,15,40};
    int M[N+1][MAX_W+1];

    printf("\n\nMax value = %d\n\n", knapsack(W,V,M));

}
