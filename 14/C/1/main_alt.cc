#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common.h"

const int STEPS = 10;

// DO NOT USE FOR PART 2! POLYMER IS BUILT IN MEMORY
int main() {
    read_input();
    int polymer_size = (1 << STEPS) * (template_size - 1) + 1;
    u8* polymer = (u8*)malloc(polymer_size);
    int step_size = polymer_size / (template_size - 1);
    for (int i = 0, j = 0; i < polymer_size; i += step_size, ++j) {
        polymer[i] = polymer_template[j];
    }
    iter: {
        step_size >>= 1;
    } while ( step_size > 0) {
        for (int i = step_size; i < polymer_size; i += 2 * step_size) {
            polymer[i] = pair[polymer[i - step_size]][polymer[i + step_size]];
        }
        goto iter;
    }

    for (int i = 0; i < polymer_size; ++i) {
        ++elements_count[polymer[i]];
    }
    free(polymer);

    printf("%I64d", calc_ans_by_elements_count());
    return 0;
}
