#include <stdio.h>
#define N 10


int dice_throw_dp(int f, int d, int s) {
    int DPTable[N][N] = {0};
    int i, j;
    for (i=1;i<=d;i++) {
        for (j = i; j <= s; j++) {
            DPTable[i][j] = DPTable[i][j-1] + DPTable[i-1][j-1];
            if (j > f) {
                DPTable[i][j] -= DPTable[i-1][j-f-1];
            }
        }
    }

    return DPTable[d][s];
}

int main() {
    //d <= N && s <= N
    printf("\n\n%d", dice_throw_dp(4, 2, 1));
    printf("\n\n%d", dice_throw_dp(2, 3, 3));
    printf("\n\n%d", dice_throw_dp(6, 3, 8));
    printf("\n\n%d", dice_throw_dp(5, 3, 8));
    printf("\n\n%d", dice_throw_dp(4, 3, 5));
    return 0;
}
