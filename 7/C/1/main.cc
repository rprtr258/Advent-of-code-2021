#include <stdio.h>
#include "../common.h"

int partition(int l, int r) {
    int pivot = x[(l + r) / 2];
    int pl = l, pr = r - 1;
    while (pl < pr) {
        while (x[pr] > pivot) {
            --pr;
        }
        while (x[pl] < pivot) {
            ++pl;
        }
        x[pl] ^= x[pr] ^= x[pl] ^= x[pr];
        ++pl;
        --pr;
    }
    return pl;
}

int find_median(int l, int r, int k) {
    if (r == l + 1) {
        return l;
    }
    int m = partition(l, r);
    if (m - l > k) {
        return find_median(l, m, k);
    } else {
        return find_median(m, r, k - (m - l));
    }
}

int main() {
    read_input();
    int median = x[find_median(0, len, len / 2)];
    int ans = 0;
    for (int i = 0; i < len; ++i) {
        ans += abs(x[i] - median);
    }
    printf("%d", ans);
    return 0;
}
