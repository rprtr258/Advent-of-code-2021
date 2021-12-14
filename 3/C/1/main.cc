#include <stdio.h>

const unsigned int SIZE = 12;
char row[SIZE + 2];
int total = 0;
int counter[SIZE];

int main() {
    for (int i = 0; i < SIZE; i++) {
        counter[i] = 0;
    }
    while (fgets(row, sizeof(row), stdin)) {
        for (int i = 0; i < SIZE; i++) {
            counter[i] += row[i] - '0';
        }
        ++total;
    }
    int gamma = 0;
    for (int i = 0; i < SIZE; i++) {
        gamma = gamma * 2 + (counter[i] >= total / 2);
    }
    printf("%d", gamma * (~gamma & 0xFFF));
    return 0;
}
