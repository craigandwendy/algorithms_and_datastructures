#include <stdio.h>
#include <math.h>

#define N 20

int BinSearch(int Arr[], int v) {
    int l = 0;
    int r = N-1;
    int m = floor((l+r)/2);

    while (l <= r && Arr[m] != v) {
        if (v <= Arr[m]) {
            r = m - 1;
        } else {
            l = m + 1;
        }
        m = floor((l+r)/2);
    }

    if (l <= r) {
        return m;
    }
    return -1;
}

int main() {
    int Arr[N] = {1, 5, 7, 9, 12, 41, 64, 82, 91, 100, 111, 139, 160, 189, 213, 254, 273, 299, 341, 391};

    int v = 12;

    int res = BinSearch(Arr, v);

    if (res == -1) {
        printf("Element %d is not in Array.", v);
    } else {
        printf("Element %d is at index position %d.", v, res);
    }

    return 0;
}
