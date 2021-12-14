#include <stdio.h>
#include "../common.h"

int main() {
    read_input();
    int ans = 0;
    for (int i = 0; i < 100; ++i) {
        ans += step();
    }
    printf("%d", ans);
}
