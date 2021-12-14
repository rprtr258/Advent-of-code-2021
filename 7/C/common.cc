#include <stdio.h>
#include "common.h"

int x[1000];
int len = 0;

int abs(int x) {
    return (x > 0 ? x : -x);
}

void read_input() {
    while (!feof(stdin)) {
        scanf("%d,", &x[len]);
        ++len;
    }
}
