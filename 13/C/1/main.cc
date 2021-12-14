#include <stdio.h>
#include "../common.h"

int main() {
    read_coords();
    read_folding();
    int ans = 0;
    FOR_EVERY_COORD(cur) {
        FOR_COORD(cur2, coords, cur) {
            if (X(cur2) == X(cur) && Y(cur2) == Y(cur)) {
                goto SKIP_CHECK;
            }
        }
        ++ans;
        SKIP_CHECK:;
    }
    printf("%d", ans);
    return 0;
}
