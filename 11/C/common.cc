#include <stdio.h>
#include <string.h>
#include "common.h"

const int BUF_SIZE = 50;
char map[BUF_SIZE][BUF_SIZE];
int w = 0, h = 0;

void read_input() {
    char (*buf)[BUF_SIZE] = (char(*)[BUF_SIZE])&map[1][1];
    while (!feof(stdin)) {
        scanf("%s", buf);
        for (char* cur = *buf; *cur; ++cur) {
            *cur -= '0';
        }
        ++buf;
    }
    h = buf - map - 1;
    w = strlen(&map[1][1]);
}

int step() {
    int res = 0;
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            map[i][j] += 1;
        }
    }
    bool was_updated = true;
    while (was_updated) {
        was_updated = false;
        for (int i = 1; i <= h; ++i) {
            for (int j = 1; j <= w; ++j) {
                if (map[i][j] <= 9) {
                    continue;
                }
                map[i][j] = 0;
                ++res;
                was_updated = true;
                if (map[i - 1][j - 1] != 0) {
                    ++map[i - 1][j - 1];
                }
                if (map[i - 1][j] != 0) {
                    ++map[i - 1][j];
                }
                if (map[i - 1][j + 1] != 0) {
                    ++map[i - 1][j + 1];
                }
                if (map[i][j - 1] != 0) {
                    ++map[i][j - 1];
                }
                if (map[i][j] != 0) {
                    ++map[i][j];
                }
                if (map[i][j + 1] != 0) {
                    ++map[i][j + 1];
                }
                if (map[i + 1][j - 1] != 0) {
                    ++map[i + 1][j - 1];
                }
                if (map[i + 1][j] != 0) {
                    ++map[i + 1][j];
                }
                if (map[i + 1][j + 1] != 0) {
                    ++map[i + 1][j + 1];
                }
            }
        }
    }
    return res;
}
