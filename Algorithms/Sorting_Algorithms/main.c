#include <stdio.h>
#define n 7

void insertion_sort(int Arr[]) {
    int i, j, t;
    for (i=1;i<n;i++) {
        j = i-1;
        t = Arr[i];
        while (j >= 0 && Arr[j] > t) { /*Arr[j] < t --> sort in reverse order*/
            Arr[j+1] = Arr[j];
            j = j-1;
        }
        Arr[j+1] = t;
    }
}

void print_array(int Arr[]) {
    int i;
    for (i=0;i<n;i++) {
        if (i+1 == n) {
            printf("%d\n", Arr[i]);
        } else {
            printf("%d, ", Arr[i]);
        }
    }
}


int main() {
    int Arr[7] = {7, 4, 8, 5, 6, 2, 3};
    insertion_sort(Arr);
    print_array(Arr);
}