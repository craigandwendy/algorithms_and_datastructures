#include <stdio.h>
#define n 7

void swap(int *A, int *B) {
    int temp = *A;
    *A = *B;
    *B = temp;

}

void selection_sort(int Arr[]) {
    int i, j, k;
    for (i=0;i<n-1;i++) {
        k = i;
        for (j=i+1;j<n;j++) {
            if (Arr[j] < Arr[k]) {
                k = j;
            }
        }
        swap(&Arr[i], &Arr[k]);
        /*int temp = Arr[i];
        Arr[i] = Arr[k];
        Arr[k] = temp;*/ /*--> swapping without new function*/
    }
}

void modified_selection_sort(int Arr[]) {
    /*modify selection sort such, that it selects the largest element and swaps with the last element of corresponding subarray*/
    int i,j,k;
    for (i=n-1;i>1;i--) {
        k = i;
        for (j=i-1;j>=0;j--) {
            if (Arr[j] > Arr[k]) {
                k = j;
            }
        }
        swap(&Arr[i], &Arr[k]);
    }
}

void print_array(int Arr[]) {
    int i;
    for (i=0;i<n;i++) {
        if (i+1 == n) {
            printf("%d", Arr[i]);
        } else {
            printf("%d, ", Arr[i]);
        }
    }
}

int main() {
    int Arr[n] = {8, 4, 7, 3, 2, 5, 6};
    modified_selection_sort(Arr);
    print_array(Arr);
}