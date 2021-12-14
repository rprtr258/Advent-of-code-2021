#include <stdio.h>
#include "../common.h"

#define CHAR(code, ch) case code: {putchar(ch);} break;

int main() {
    read_coords();
    while (!feof(stdin)) {
        read_folding();
    }
    const int LETTERS_COUNT = 8;
    const int LETTER_WIDTH = 4;
    const int LETTER_WIDTH_WITH_MARGIN = LETTER_WIDTH + 1;
    int letters_signature[LETTERS_COUNT] = {};
    FOR_EVERY_COORD(cur) {
        int letter_index = X(cur) / LETTER_WIDTH_WITH_MARGIN;
        int x = X(cur) % LETTER_WIDTH_WITH_MARGIN;
        int y = Y(cur);
        int bit_pos = x + y * LETTER_WIDTH;
        letters_signature[letter_index] |= 1 << bit_pos;
    }
    for (int i = 0; i < 8; ++i) {
        switch (letters_signature[i]) {
            CHAR(0x799797, 'B')
            CHAR(0xF1171F, 'E')
            CHAR(0x955359, 'K')
            CHAR(0xF11111, 'L')
            CHAR(0x117997, 'P')
            CHAR(0x957997, 'R')
            // OTHER LETTERS MUST BE ADDED
        }
    }
    return 0;
}
