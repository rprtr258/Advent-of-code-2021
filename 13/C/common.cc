#include <stdio.h>
#include "common.h"

#define ISDIGIT(x) ('0' <= x && x <= '9')
#define DIGIT_TO_SHORT(x) (x - '0')

const int COORDS_SIZE = 1000;

u16_2 coords[COORDS_SIZE];
u16_2* coords_end;
int coords_size = 0;

short read_num() {
    char c = getchar();
    if (!ISDIGIT(c)) {
        return -1;
    }
    short res = DIGIT_TO_SHORT(c);
    iter: {
        c = getchar();
    } while (!feof(stdin)) {
        if ISDIGIT(c) {
            res = res * 10 + DIGIT_TO_SHORT(c);
        } else {
            break;
        }
        goto iter;
    }
    return res;
}

void read_coords() {
    for (;;) {
        short x = read_num();
        if (x == -1) {
            break;
        }
        short y = read_num();
        coords[coords_size][0] = x;
        coords[coords_size][1] = y;
        ++coords_size;
    }
    coords_end = coords + coords_size;
}

void read_folding() {
    for (int i = 0; i < 11; ++i) { // "fold along "
        getchar();
    }
    char coord = getchar();
    getchar(); // "="
    short value = read_num();
    int coord_int = (coord == 'x' ? 0 : 1);
    FOR_EVERY_COORD(cur) {
        if ((*cur)[coord_int] > value) {
            (*cur)[coord_int] = 2 * value - (*cur)[coord_int];
        }
    }
}
