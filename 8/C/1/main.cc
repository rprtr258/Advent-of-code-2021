#include <stdio.h>

int main() {
    char buf[100];
    int ans = 0;
    while (!feof(stdin)) {
        for (int i = 0; i < 11; ++i) {
            scanf("%s", buf);
        }
        for (int i = 0; i < 4; ++i) {
            int len = 0;
            scanf("%s", buf);
            while (buf[len]) {
                ++len;
            }
            if (len == 2 || len == 3 || len == 4 || len == 7) {
                ++ans;
            }
        }
    }
    printf("%d", ans);
}
