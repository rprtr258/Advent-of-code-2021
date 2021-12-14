#include <stdio.h>
#include <string.h>
#include "common.h"

#define FOR_ELEMENTS(x) for (int x = 0; x < elements_size; ++x)

u8 polymer_template[MAX_TEMPLATE_SIZE];
u8 template_size;

u8 elements[MAX_ELEMENTS];
int elements_size;

u8 pair[MAX_ELEMENTS][MAX_ELEMENTS];
i64 dp[MAX_ELEMENTS][MAX_ELEMENTS];
i64 dp_new[MAX_ELEMENTS][MAX_ELEMENTS];
i64 elements_count[MAX_ELEMENTS];

u8 insert(char c) {
    u8 *cur, *end;
    for (cur = elements, end = elements + elements_size; cur != end; ++cur) {
        if (*cur == c) {
            return cur - elements;
        }
    }
    *cur = c;
    return elements_size++;
}

u8 strlen(u8* str) {
    u8* cur;
    for (cur = str; *cur; ++cur)
        ;
    return cur - str;
}

void read_input() {
    scanf("%s\n", polymer_template);
    template_size = strlen(polymer_template);
    for (u8 i = 0; i < template_size; ++i) {
        polymer_template[i] = insert(polymer_template[i]);
    }

    while (!feof(stdin)) {
        char a, b, c;
        scanf("%c%c -> %c\n", &a, &b, &c);
        u8 a_index = insert(a);
        u8 b_index = insert(b);
        u8 c_index = insert(c);
        pair[a_index][b_index] = c_index;
    }
}

i64 calc_ans_by_elements_count() {
    i64 min = I64_MAX, max = -1;
    FOR_ELEMENTS(i) {
        if (elements_count[i] > max) {
            max = elements_count[i];
        }
        if (elements_count[i] < min) {
            min = elements_count[i];
        }
    }
    return max - min;
}

i64 solve(int steps) {
    read_input();
    memset(dp, 0, MAX_ELEMENTS * MAX_ELEMENTS * sizeof(i64));
    for (u8 i = 0; i < template_size - 1; ++i) {
        ++dp[polymer_template[i]][polymer_template[i + 1]];
    }

    for (int step = 0; step < steps; ++step) {
        memset(dp_new, 0, MAX_ELEMENTS * MAX_ELEMENTS * sizeof(i64));
        FOR_ELEMENTS(a) {
            FOR_ELEMENTS(b) {
                u8 m = pair[a][b];
                i64 value = dp[a][b];
                dp_new[a][m] += value;
                dp_new[m][b] += value;
            }
        }
        memcpy(dp, dp_new, MAX_ELEMENTS * MAX_ELEMENTS * sizeof(i64));
    }

    ++elements_count[polymer_template[0]];
    ++elements_count[polymer_template[template_size - 1]];
    FOR_ELEMENTS(a) {
        FOR_ELEMENTS(b) {
            elements_count[a] += dp[a][b];
            elements_count[b] += dp[a][b];
        }
    }

    return calc_ans_by_elements_count() / 2;
}
