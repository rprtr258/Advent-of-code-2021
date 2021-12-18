#include <stdio.h>
#include <string.h>

const int MAP_SIZE = 101;

char map[MAP_SIZE][MAP_SIZE];
int real_height = 0, real_width = 0, virtual_height, virtual_width;
short dp[MAP_SIZE * 5][MAP_SIZE * 5];

char virtual_map(int virtual_y, int virtual_x) {
    int real_y = virtual_y % real_height;
    int real_x = virtual_x % real_width;
    char delta = (virtual_y / real_height) + (virtual_x / real_width);
    return (map[real_y][real_x] - 1 + delta) % 9 + 1;
}

void read_input() {
    char (*row)[MAP_SIZE] = map;
    while (!feof(stdin)) {
        scanf("%s", *row);
        for (char* cur = row[0]; *cur; ++cur) {
            *cur -= '0';
        }
        ++row;
    }
    real_height = row - map;
    virtual_height = real_height * 5;
    while (map[0][real_width])
        ++real_width;
    virtual_width = real_width * 5;
}

void calc_dp() {
    for (int x = 1; x < virtual_width; ++x) {
        if (dp[0][x] > dp[0][x - 1] + virtual_map(0, x)) {
            dp[0][x] = dp[0][x - 1] + virtual_map(0, x);
        }
    }
    for (int y = 1; y < virtual_height; ++y) {
        if (dp[y][0] > dp[y - 1][0] + virtual_map(y, 0)) {
            dp[y][0] = dp[y - 1][0] + virtual_map(y, 0);
        }
        for (int x = 1; x < virtual_width; ++x) {
            if (dp[y][x] > dp[y - 1][x] || dp[y][x] > dp[y][x - 1]) {
                if (dp[y - 1][x] > dp[y][x - 1]) {
                    dp[y][x] = dp[y][x - 1];
                } else {
                    dp[y][x] = dp[y - 1][x];
                }
                dp[y][x] += virtual_map(y, x);
            }
        }
    }
}

void update() {
    for (int y = 0; y < virtual_height; ++y) {
        for (int x = 0; x < virtual_width; ++x) {
            if (y + 1 < virtual_height && dp[y][x] > dp[y + 1][x] + virtual_map(y, x)) {
                dp[y][x] = dp[y + 1][x] + virtual_map(y, x);
            }
            if (x + 1 < virtual_width && dp[y][x] > dp[y][x + 1] + virtual_map(y, x)) {
                dp[y][x] = dp[y][x + 1] + virtual_map(y, x);
            }
        }
    }
}

int main() {
    read_input();
    memset(dp, 0x7F, sizeof(dp));
    dp[0][0] = 0;
    calc_dp();
    for (;;) {
        short old_ans = dp[virtual_height - 1][virtual_width - 1];
        update();
        calc_dp();
        if (old_ans == dp[virtual_height - 1][virtual_width - 1]) {
            break;
        }
    }
    printf("%d", dp[virtual_height - 1][virtual_width - 1]);
    return 0;
}
