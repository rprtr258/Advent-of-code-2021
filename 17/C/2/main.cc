#include <stdio.h>
#include <math.h>
#include "../common.h"

bool launch(int vx, int vy) {
    int x = 0, y = 0;
    while (y + vy >= MY_y0 || vy >= 0) {
        x += vx;
        y += vy;
        if (MY_y0 <= y && y <= MY_y1 && x0 <= x && x <= x1) {
            return true;
        }
        vx = (vx == 0 ? 0 : vx - 1);
        --vy;
    }
    return MY_y0 <= y && y <= MY_y1 && x0 <= x && x <= x1;
}

int main() {
    read_input();
    int ans = 0;
    for (int vx = ceil((sqrt(1 + 8 * x0) - 1) / 2); vx <= x1; ++vx) {
        for (int vy = MY_y0; vy <= -MY_y0; ++vy) {
            ans += launch(vx, vy);
        }
    }
    printf("%d", ans);
    return 0;
}
