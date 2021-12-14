#include "stdio.h"
#include "../common.h"

void sol(int* depth, int* distance, struct Command* cmd) {
    int aim = 0;
    while (read_command(cmd) != EOF) {
        switch (cmd->dir) {
            case UP: {
                aim -= cmd->value;
            } break;
            case DOWN: {
                aim += cmd->value;
            } break;
            case FORWARD: {
                *distance += cmd->value;
                *depth += aim * cmd->value;
            } break;
        }
    }
}
