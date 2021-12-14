#include <stdio.h>
#include "../common.h"

int abs(int x) {return (x > 0 ? x : -x);}

int main() {
    struct {
        int x0, y0, x1, y1;
    } vents[1000];
    unsigned int len = 0;
    while (!feof(stdin)) {
        scanf("%d,%d -> %d,%d", &vents[len].x0, &vents[len].y0, &vents[len].x1, &vents[len].y1);
        ++len;
    }
    int ans = 0;
    for (int x = 0; x < 1000; ++x) {
        for (int y = 0; y < 1000; ++y) {
            int cnt = 0;
            for (int i = 0; i < len; ++i) {
                if (
                    (vents[i].x0 == vents[i].x1 &&
                    vents[i].x1 == x &&
                    min(vents[i].y0, vents[i].y1) <= y &&
                    y <= max(vents[i].y0, vents[i].y1)
                ) || (
                    vents[i].y0 == vents[i].y1 &&
                    vents[i].y1 == y &&
                    min(vents[i].x0, vents[i].x1) <= x &&
                    x <= max(vents[i].x0, vents[i].x1)
                ) || (
                    vents[i].x0 != vents[i].x1 &&
                    vents[i].y0 != vents[i].y1 &&
                    min(vents[i].x0, vents[i].x1) <= x &&
                    x <= max(vents[i].x0, vents[i].x1) &&
                    min(vents[i].y0, vents[i].y1) <= y &&
                    y <= max(vents[i].y0, vents[i].y1) &&
                    abs(x - vents[i].x0) == abs(y - vents[i].y0)
                )) {
                    ++cnt;
                    if (cnt == 2) {
                        ++ans;
                        break;
                    }
                }
            }
        }
    }
    printf("%d", ans);
    return 0;
}
