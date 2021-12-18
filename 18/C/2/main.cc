#include <stdio.h>
#include <stdlib.h>
#include "../common.h"

int main() {
    Tree* lines[100];
    int lines_len = 0;
    while (!feof(stdin)) {
        lines[lines_len] = read_tree();
        ++lines_len;
    }
    int ans = -1;
    for (int i = 0; i < lines_len; ++i) {
        for (int j = 0; j < lines_len; ++j) {
            if (i == j) {
                continue;
            }
            Tree* sum = add(copy(lines[i]), copy(lines[j]));
            int mag = magnitude(sum);
            if (ans < mag) {
                ans = mag;
            }
            free_tree(sum);
        }
    }
    printf("%d", ans);
    for (int i = 0; i < lines_len; ++i) {
        free_tree(lines[i]);
    }
    return 0;
}
