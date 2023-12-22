#include <stdio.h>
#define n 10

void bubble_sort(int Arr[]) {
    int i;
    int j;
    for (i=n;i>1;i--) {
        for (j=1;j<i;j++) {
            if (Arr[j] < Arr[j-1]) {
                int temp = Arr[j];
                Arr[j] = Arr[j-1];
                Arr[j-1] = temp;
            }
        }
    }
}

/*task: modify bubble sort, that at each iteration of the outer loop the smallest element of the subarray is moved to the left*/
void bubble_sort_modified (Arr[]) {
    int i;
    int j;
    for (i=1;i<n-1;i++) {
        for (j=n-1;j>=i;j--) {
            if (Arr[j] < Arr[j-1]) {
                int temp = Arr[j];
                Arr[j] = Arr[j-1];
                Arr[j-1] = temp;
            }
        }
    }
}

void print_arr(int Arr[]) {
    int i;
    for (i=0;i<n;i++) {
        if (i + 1== n) {
            printf("%d", Arr[i]);
        } else {
            printf("%d, ", Arr[i]);
        }
    }
}

void get_arr(int Arr[]) {
    int i = 0;
    int j = 0;
    while (j++ < n) {
        scanf("%d", &Arr[i++]);
    }
}

int main() {
    int Arr[n] = {1, 0, 4627, 0, 4, 3, 77, 5, 23, 68};

    /*get_arr(Arr);*/ /* --> user input (optional)*/

    /*bubble_sort(Arr);*/

    bubble_sort_modified(Arr);

    print_arr(Arr);
}