#include <stdio.h>
#include <math.h>
#define n 20

void create_array(int Arr[]) {
    int i;
    for (i=0;i<n;i++) {
        if (i == 0 || i == 1) {
            Arr[i] = 0;
        } else {
            Arr[i] = 1;
        }
    }
}

void quadratic_sieve(int Arr[]) {
    int i, j;
    for (i=2;i<n;i++) {
        for (j=i;j<n;j++) {
            if (j%i == 0 && j!= i) {
                Arr[j] = 0;
            }
        }
    }
}

void sieve_of_eratosthenes(int Arr[]) {
    int i, j;
    int _n = n;
    for (i=2;i< floor(sqrt(_n));i++) {
        for (j=i;j< floor(_n/i);j++) {
            Arr[i*j] = 0;
        }
    }

}

int main() {
    int Arr[n];
    int i;
    create_array(Arr);
    /*quadratic_sieve(Arr);*/ /* --> O(n^2)*/
    sieve_of_eratosthenes(Arr); /* --> O(n*log(n)) */

    for (i=0;i<n;i++) {
        if (Arr[i]) {
            if (i+1 == n) {
            printf("%d", i);
        } else {
                printf("%d, ", i);
            }
        }
    }
}
