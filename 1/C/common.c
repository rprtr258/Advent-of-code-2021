#include "stdio.h"

void sol(int* counter);

int read_int(int* p) {
    return scanf("%d ", p);
}

int main() {
    int counter = 0;
    sol(&counter);
    printf("%d", counter);
    return 0;
}
