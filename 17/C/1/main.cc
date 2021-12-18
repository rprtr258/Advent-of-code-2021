#include <stdio.h>
#include "../common.h"

int main() {
    read_input();
    int Y = -MY_y0 - 1;
    printf("%d", Y * (Y + 1) / 2);
    return 0;
}
