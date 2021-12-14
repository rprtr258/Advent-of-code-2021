#include <stdio.h>
 
char buf[100];

struct Key {
    int a, b, c, d, e, f, g;
};
 
int text_to_bits(char* buf) {
    int res = 0;
    while (*buf) {
        res |= 1 << (*(buf++) - 'a');
    }
    return res;
}

int strlen(char* s) {
    char* t = s;
    while (*t) {
        ++t;
    }
    return t - s;
}

Key decypher() {
    int c2, c3, c4, c5[3], c6[3];
    int c5i = 0, c6i = 0;
    for (int i = 0; i < 10; ++i) {
        scanf("%s", buf);
        int bits = text_to_bits(buf);
        // FUCK YOU, C, YOU DONT ALLOW ME TO RETURN LVALUE IN BLOCKS
        switch (strlen(buf)) {
            case 2: { c2 = bits; } break;
            case 3: { c3 = bits; } break;
            case 4: { c4 = bits; } break;
            case 5: { c5[c5i++] = bits; } break;
            case 6: { c6[c6i++] = bits; } break;
        }
    }
    int and3_235 = c5[0] & c5[1] & c5[2];
    int and2_235 = (c5[0] ^ c5[1] ^ c5[2]) & ~and3_235;
    Key key;
    key.a = c3 & ~c2;
    key.b = and2_235 & c4 & ~c2;
    key.d = c4 & ~c2 & ~key.b;
    key.e = and2_235 & ~key.b;
    key.c = 0x7F & ~(c6[0] ^ c6[1] ^ c6[2]) & ~key.d & ~key.e;
    key.f = c2 & ~key.c;
    key.g = and3_235 & ~key.a & ~key.d;
    return key;
}

int main() {
    int ans = 0;
    while (!feof(stdin)) {
        const Key key = decypher();
        getchar();
        getchar();
        int display = 0;
        for (int i = 0; i < 4; ++i) {
            scanf("%s", buf);
            int bits = text_to_bits(buf);
            int d;
            // FUCK YOU, C, YOU NEITHER ALLOW ME TO RETURN VALUE IN BLOCKS NOR SWITCH OVER NOT CONSTANTS
            if (bits == (key.a|key.b|key.c|key.e|key.f|key.g)) { d = 0; } else
            if (bits == (key.c|key.f)) { d = 1; } else
            if (bits == (key.a|key.c|key.d|key.e|key.g)) { d = 2; } else
            if (bits == (key.a|key.c|key.d|key.f|key.g)) { d = 3; } else
            if (bits == (key.b|key.c|key.d|key.f)) { d = 4; } else
            if (bits == (key.a|key.b|key.d|key.f|key.g)) { d = 5; } else
            if (bits == (key.a|key.b|key.d|key.e|key.f|key.g)) { d = 6; } else
            if (bits == (key.a|key.c|key.f)) { d = 7; } else
            if (bits == (key.a|key.b|key.c|key.d|key.e|key.f|key.g)) { d = 8; } else
            if (bits == (key.a|key.b|key.c|key.d|key.f|key.g)) { d = 9; }
            display = display * 10 + d;
        }
        ans += display;
    }
    printf("%d", ans);
}
