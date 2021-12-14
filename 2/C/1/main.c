#include "stdio.h"
#include "../common.h"

void sol(int* depth, int* distance, struct Command* cmd) {
    while (read_command(cmd) != EOF) {
        switch (cmd->dir) {
            case UP: {
                *depth -= cmd->value;
            } break;
            case DOWN: {
                *depth += cmd->value;
            } break;
            case FORWARD: {
                *distance += cmd->value;
            } break;
        }
    }
}
