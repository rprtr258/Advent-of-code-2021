#include "stdio.h"

int read_int(int* p);

void sol(int* counter) {
    int sum = 0;
    int window[4];
    for (int i = 0; i < 3; i++) {
        read_int(window + i);
        sum += window[i];
    }
    while (read_int(window + 3) != EOF) {
        int next_sum = sum + window[3] - window[0];
        *counter += next_sum > sum;
        for (int i = 0; i < 3; i++) {
            window[i] = window[i + 1];
        }
    }
}
