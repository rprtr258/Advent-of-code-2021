#include <stdio.h>
#include "../common.h"

int cost(int y) {
    int res = 0;
    for (int i = 0; i < len; ++i) {
        int d = abs(x[i] - y);
        res += d * (d + 1) / 2;
    }
    return res;
}

int min(int a, int b) {
    return (a < b ? a : b);
}

int main() {
    read_input();
    int mean = 0;
    for (int i = 0; i < len; ++i) {
        mean += x[i];
    }
    mean /= len;
    int ans = min(cost(mean), cost(mean + 1));
    printf("%d", ans);
    return 0;
}
