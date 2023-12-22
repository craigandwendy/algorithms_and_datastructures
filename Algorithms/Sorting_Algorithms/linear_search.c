#include <stdio.h>

#define n 10

int LinSearch_1(int Arr[], int v) {
    int p = NULL;
    int i;
    for (i=0;i<n;i++) {
        if (Arr[i] == v) {
            p = v;
        }
    }
    return p;
}

int LinSearch_2(int Arr[], int v) {
    int i = 0;
    while (i<=n && Arr[i] != v) {
        i++;
    }
    if (i <= n) {
        return i;
    }
    return NULL;
}

int LinSearch_4(int Arr[], int v) {
    int i;
    for (i=0;i<n;i++) {
        if (Arr[i] == v) {
            return i;
        }
    }
    return NULL;
}


int main() {
    int Arr[] = {4,5,7,2,6,8,0,2,1,5};
    int v = 1;
    printf("%d", LinSearch_1(Arr, v));
    printf("%d", LinSearch_2(Arr, v));
    printf("%d", LinSearch_4(Arr, v));
    /*LinSearch_2 & LinSearch_4 are equivalent */
}
