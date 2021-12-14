#include <stdio.h>
#include <string.h>

const int BUF_SIZE = 101;

int m[3] = {-1, -1, -1}, min_m = 0;
int width = 0, height = 0;
char map[BUF_SIZE][BUF_SIZE];
bool visited[BUF_SIZE][BUF_SIZE];

struct Pair {
    int i, j;
};

int bfs(Pair start) {
    const int RING_SIZE = 300;
    Pair ring[RING_SIZE];
    int l = 0, r = 1;
    ring[0] = start;
    visited[start.i][start.j] = true;
    int res = 0;
    while (l != r) {
        int i = ring[l].i, j = ring[l].j;
        ++res;
        l = (l + 1) % RING_SIZE;
        if (i > 0 && map[i - 1][j] != '9' && !visited[i - 1][j]) {
            visited[i - 1][j] = true;
            ring[r] = Pair {.i = i - 1, .j = j};
            r = (r + 1) % RING_SIZE;
        }
        if (i < height - 1 && map[i + 1][j] != '9' && !visited[i + 1][j]) {
            visited[i + 1][j] = true;
            ring[r] = Pair {.i = i + 1, .j = j};
            r = (r + 1) % RING_SIZE;
        }
        if (j > 0 && map[i][j - 1] != '9' && !visited[i][j - 1]) {
            visited[i][j - 1] = true;
            ring[r] = Pair {.i = i, .j = j - 1};
            r = (r + 1) % RING_SIZE;
        }
        if (j < width - 1 && map[i][j + 1] != '9' && !visited[i][j + 1]) {
            visited[i][j + 1] = true;
            ring[r] = Pair {.i = i, .j = j + 1};
            r = (r + 1) % RING_SIZE;
        }
    }
    return res;
}

int main() {
    char (*cur)[BUF_SIZE] = map;
    while (!feof(stdin)) {
        scanf("%s", cur);
        ++cur;
        ++height;
    }
    width = strlen(cur[-1]);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (!visited[i][j] && map[i][j] != '9') {
                int basin_size = bfs(Pair {.i = i, .j = j});
                if (basin_size > m[min_m]) {
                    m[min_m] = basin_size;
                    min_m = (m[0] < m[1] && m[0] < m[2] ? 0 : (m[1] < m[0] && m[1] < m[2] ? 1 : 2));
                }
            }
        }
    }
    printf("%d", m[0] * m[1] * m[2]);
}
