#include <stdio.h>


int FibDP(int n) {
    // fib(n) = fib(n-1) + fib(n-1) [fib(0) = 0, fib(1) = 1]
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    int fib_a = 0;
    int fib_b = 1;
    int i, fib_c;
    for (i=2;i<=n;i++) {
        fib_c = fib_a + fib_b;
        fib_a = fib_b;
        fib_b = fib_c;
    }
    return fib_c;
}

int main() {
    int i;
    for (i=0;i<25;i++) {
        printf("fib(%d) = %d\n", i, FibDP(i));
    }
    return 0;
}
