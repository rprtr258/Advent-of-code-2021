#include <stdio.h>
#include "../common.h"

long long scores[200];
long long* scores_cur = scores;

int main() {
    while (!feof(stdin)) {
        long long tmp = get_score();
        if (tmp < 0) {
            *scores_cur++ = -tmp;
        }
    }
    int len = scores_cur - scores;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (scores[i] > scores[j]) {
                scores[i] ^= scores[j] ^= scores[i] ^= scores[j];
            }
        }
    }
    printf("%I64d", scores[len / 2]);
}
