#include "stdio.h"
#include "common.h"

void sol(int*, int*, struct Command*);

int read_command(struct Command* c) {
    char cmd[10];
    int res = scanf("%s %d ", cmd, &c->value);
    if (res) {
        switch (cmd[0]) {
            case 'u': {
                c->dir = UP;
            } break;
            case 'd': {
                c->dir = DOWN;
            } break;
            case 'f': {
                c->dir = FORWARD;
            } break;
        }
    }
    return res;
}

int main() {
    int depth = 0;
    int distance = 0;
    struct Command cmd;
    sol(&depth, &distance, &cmd);
    printf("%d", distance * depth);
    return 0;
}
