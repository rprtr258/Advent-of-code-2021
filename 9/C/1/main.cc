#include <stdio.h>
#include <string.h>

const int BUF_SIZE = 101;

int ans = 0;

void update_ans(char d) {
    ans += d - '0' + 1;
}

void check_border(char (*row1)[BUF_SIZE], char (*row2)[BUF_SIZE]) {
    if ((*row1)[0] < (*row1)[1] && (*row1)[0] < (*row2)[0]) {
        update_ans((*row1)[0]);
    }
    int i;
    for (i = 1; (*row1)[i + 1]; ++i) {
        if ((*row1)[i] < (*row1)[i - 1] && (*row1)[i] < (*row1)[i + 1] && (*row1)[i] < (*row2)[i]) {
            update_ans((*row1)[i]);
        }
    }
    if ((*row1)[i] < (*row1)[i - 1] && (*row1)[i] < (*row2)[i]) {
        update_ans((*row1)[i]);
    }
}

int main() {
    char row1[BUF_SIZE], row2[BUF_SIZE], row3[BUF_SIZE];
    scanf("%s", row1);
    scanf("%s", row2);
    check_border(&row1, &row2);
    while (!feof(stdin)) {
        scanf("%s", row3);
        if (row2[0] < row2[1] && row2[0] < row1[0] && row2[0] < row3[0]) {
            update_ans(row2[0]);
        }
        int i;
        for (i = 1; row2[i + 1]; ++i) {
            if (row2[i] < row2[i - 1] && row2[i] < row2[i + 1] && row2[i] < row1[i] && row2[i] < row3[i]) {
                update_ans(row2[i]);
            }
        }
        if (row2[i] < row2[i - 1] && row2[i] < row1[i] && row2[i] < row3[i]) {
            update_ans(row2[i]);
        }
        memcpy(row1, row2, BUF_SIZE);
        memcpy(row2, row3, BUF_SIZE);
    }
    check_border(&row2, &row1);
    printf("%d", ans);
}
