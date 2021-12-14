#include <stdio.h>
#include <functional>

typedef unsigned int u32;

const u32 SIZE = 12, TOTAL = 1000;
char rows[TOTAL][SIZE + 2];

void read_input() {
    for (u32 i = 0; i < TOTAL; ++i) {
        fgets(rows[i], sizeof(rows[i]), stdin);
    }
}

void sort() {
    for (u32 i = 0; i < TOTAL; ++i) {
        for (u32 j = i + 1; j < TOTAL; ++j) {
            bool do_swap = false;
            for (u32 k = 0; k < SIZE; ++k) {
                if (rows[i][k] != rows[j][k]) {
                    do_swap = rows[i][k] > rows[j][k];
                    break;
                }
            }
            if (!do_swap) {
                continue;
            }
            for (u32 k = 0; k < SIZE; ++k) {
                char tmp = rows[i][k];
                rows[i][k] = rows[j][k];
                rows[j][k] = tmp;
            }
        }
    }
}

u32 binsearch(const u32 bit, u32 l, u32 r) {
    while (r > l + 1) {
        u32 m = (l + r) >> 1;
        (rows[m][bit] == '0' ? l : r) = m;
    }
    return r;
}

u32 from_binary(const u32 i) {
    u32 res = 0;
    for (u32 k = 0; k < SIZE; ++k) {
        res = (res << 1) + (rows[i][k] - '0');
    }
    return res;
}

u32 get_rating(const std::function<bool(u32, u32)> size_comparator) {
    u32 l = 0, r = TOTAL;
    for (u32 k = 0; r > l + 1 && k < SIZE; ++k) {
        u32 m = binsearch(k, l, r);
        (size_comparator(m - l, r - m) ? l : r) = m;
    }
    return from_binary(l);
}

int main() {
    read_input();
    sort();
    u32 oxygen_generator_rating = get_rating([](uint32 size_0, uint32 size_1) {return size_0 <= size_1;});
    u32 co2_scrubber_rating = get_rating([](uint32 size_0, uint32 size_1) {return size_0 > size_1;});
    printf("%u", oxygen_generator_rating * co2_scrubber_rating);
    return 0;
}
