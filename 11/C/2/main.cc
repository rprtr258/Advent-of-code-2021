#include <stdio.h>
#include "../common.h"

extern int w, h;

int main() {
    read_input();
    int ans;
    for (ans = 1; step() != w * h; ++ans)
        ;
    printf("%d", ans);
}
