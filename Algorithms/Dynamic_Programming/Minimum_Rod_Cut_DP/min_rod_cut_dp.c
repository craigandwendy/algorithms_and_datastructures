#include <stdio.h>
#define N 11

int Price[N] = {0,1,3,4,5,6,7,8,11,12,13};

int cutMemo(int length, int MaxRevenueTable[]);

int cut(int length) {
    if (length == 0) {
        return 0;
    }
    int MaxRevenueTable[N] = {0};
    cutMemo(length, MaxRevenueTable);

    //int i;
    //for (i=0;i<=length;i++) {
    //    printf("%d, ", MaxRevenueTable[i]);
    //}

    return MaxRevenueTable[length];
}

int cutMemo (int length, int MaxRevenueTable[]) {
    if (MaxRevenueTable[length] == 0) { //no optimal solution found yet
        int i, temp;
        for (i=1;i<=length;i++) { //check all possibilities
            temp = Price[i] + cutMemo(length - i, MaxRevenueTable);
            if (temp > MaxRevenueTable[length]) { //check if temp is better than solution in table
                MaxRevenueTable[length] = temp; //temp becomes new optimal solution
            }
        }
    }
    return MaxRevenueTable[length]; //return optimal solution
}

int Maximum(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int cutDp(int length) {
    if (length == 0) {
        return 0;
    }
    int RevenueMatrix[N][N] = {0};
    int i,j;
    for (i=1;i<=length;i++) {
        for (j=0;j<=length;j++) {
            if (i==1) {
                RevenueMatrix[i][j] = Price[i]*j;
            } else {
                if (j>=i) {
                    RevenueMatrix[i][j] = Maximum(Price[i] + RevenueMatrix[i][j - i], RevenueMatrix[i - 1][j]);
                }
                else {
                    RevenueMatrix[i][j] = RevenueMatrix[i-1][j];
                }
            }
        }
    }

    for (i=0;i<=length;i++) {
        for (j=0;j<=length;j++) {
            printf("%d ", RevenueMatrix[i][j]);
        }
        printf("\n");
    }

    //return RevenueMatrix[N-1][length]; //returns maxRevenue for any length up to N-1
    int cuts = 0;
    i = length;
    j = length;

    if (RevenueMatrix[i][j]-RevenueMatrix[i][j-length] == Price[i]) {
        return cuts;
    }

    while (j > 0) {
        while (RevenueMatrix[i][j] == RevenueMatrix[i-1][j]) {
            if (RevenueMatrix[i][j]-RevenueMatrix[i][j-length] == Price[i]) {
                return cuts+1;
            }
            i--;
        }
        cuts += 1;
        while (RevenueMatrix[i][j] != RevenueMatrix[i-1][j]) {
            return cuts+1;
        }
    }

    return cuts;


}


int main() {
    int i;
    printf("\n\n%d", cutDp(10));
    return 0;
}
