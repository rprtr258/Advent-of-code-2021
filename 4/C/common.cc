#include <stdio.h>
#include <functional>
#include "common.h"

u32 number_ordering[100];

u32 update_calc(std::function<u32(u32, u32)> get) {
    u32 res = U32_MAX;
    for (u32 i = 0; i < 5; ++i) {
        u32 line_res = 0;
        for (u32 j = 0; j < 5; ++j) {
            u32 ordering = number_ordering[get(i, j)];
            line_res = (line_res < ordering ? ordering : line_res);
        }
        if (res > line_res) {
            res = line_res;
        }
    }
    return res;
}

void read_matrix(matrix* m, u32* time) {
    for (u32 i = 0; i < 5; ++i) {
        for (u32 j = 0; j < 5; ++j) {
            char c;
            iter: {
                c = getc(stdin);
            } while (c == ' ' || c == '\n' || c == '\r') {
                goto iter;
            }
            (*m)[i][j] = 0;
            iter2: {
                (*m)[i][j] = (*m)[i][j] * 10 + (c - '0');
                c = getc(stdin);
            } while ('0' <= c && c <= '9') {
                goto iter2;
            }
        }
    }
    u32 min_row_time = update_calc([m](u32 i, u32 j) {return (*m)[i][j];});
    u32 min_col_time = update_calc([m](u32 i, u32 j) {return (*m)[j][i];});
    *time = (min_row_time < min_col_time ? min_row_time : min_col_time);
}

void sol(std::function<bool(u32, u32)> cmp) {
    {
        char buf[300];
        scanf("%s", buf);
        u32 number = 0, i = 0;
        char* cur = buf;
        iter: {
            if ('0' <= *cur && *cur <= '9') {
                number = number * 10 + (*cur - '0');
            } else {
                number_ordering[number] = i;
                ++i;
                number = 0;
            }
        } while (*cur) {
            ++cur;
            goto iter;
        }
    }
    matrix ans;
    u32 min_time;
    {
        read_matrix(&ans, &min_time);
        while (!feof(stdin)) {
            matrix cur;
            u32 cur_time;
            read_matrix(&cur, &cur_time);
            if (cmp(min_time, cur_time)) {
                min_time = cur_time;
                memcpy(ans, cur, sizeof(matrix));
            }
        }
    } {
        int sum_unmarked = 0;
        int last;
        for (u32 i = 0; i < 5; ++i) {
            for (u32 j = 0; j < 5; ++j) {
                u32 ordering = number_ordering[ans[i][j]];
                if (ordering > min_time) {
                    sum_unmarked += ans[i][j];
                } else if (ordering == min_time) {
                    last = ans[i][j];
                }
            }
        }
        printf("%d", sum_unmarked * last);
    }
}
