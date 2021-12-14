#include <stdio.h>
#include "../common.h"

int main() {
    long long ans = 0;
    while (!feof(stdin)) {
        long long tmp = get_score();
        if (tmp > 0) {
            ans += tmp;
        }
    }
    printf("%I64d", ans);
}
