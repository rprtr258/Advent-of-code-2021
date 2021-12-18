#include <stdio.h>
#include <stdlib.h>
#include "../common.h"

int main() {
    Tree* res = read_tree();
    while (!feof(stdin)) {
        res = add(res, read_tree());
    }
    printf("%d", magnitude(res));
    free_tree(res);
    return 0;
}
