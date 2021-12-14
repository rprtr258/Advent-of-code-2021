#include "stdio.h"

int read_int(int* p);

void sol(int* counter) {
    int prev, next;
    read_int(&prev);
    while (read_int(&next) != EOF) {
        *counter += next > prev;
        prev = next;
    }
}
