#include <string.h>
#include <stdio.h>
#include "common.h"

typedef i64 vec9[9];
typedef i64 matrix[9][9];

matrix res;

void matrix_zero(matrix* dst) {
    memset(dst, 0, sizeof(matrix));
}

void matrix_mul(matrix* dst, matrix* tmp, matrix* a, matrix* b) {
    matrix_zero(tmp);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            for (int k = 0; k < 9; ++k) {
                (*tmp)[i][j] += (*a)[i][k] * (*b)[k][j];
            }
        }
    }
    memcpy(dst, tmp, sizeof(matrix));
}

void pow(i32 n) {
    matrix r;
    matrix_zero(&r);
    for (int i = 0; i < 9; ++i) {
        r[i][i] = 1;
    }
    matrix tmp;
    while (n) {
        if (n & 1) {
            matrix_mul(&r, &tmp, &r, &res);
        }
        matrix_mul(&res, &tmp, &res, &res);
        n >>= 1;
    }
    memcpy(res, r, sizeof(matrix));
}

i64 get_ans(i32 days) {
    vec9 v;
    memset(&v, 0, sizeof(vec9));
    while (!feof(stdin)) {
        int x;
        scanf("%d,", &x);
        ++v[x];
    }
    for (int i = 0; i < 8; ++i) {
        res[i][i + 1] = 1;
    }
    res[6][0] = 1;
    res[8][0] = 1;
    pow(days);
    i64 ans = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            ans += v[j] * res[i][j];
        }
    }
    return ans;
}
