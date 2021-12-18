#include <stdio.h>

const int MAP_SIZE = 101;

char map[MAP_SIZE][MAP_SIZE];
int height = 0, width = 0;
int dist[MAP_SIZE][MAP_SIZE];
int f[MAP_SIZE][MAP_SIZE];
bool in_heap[MAP_SIZE][MAP_SIZE];
bool in_closed[MAP_SIZE][MAP_SIZE];
struct {
    int y, x;
} heap[MAP_SIZE * MAP_SIZE];
int heap_size = 0;

void read_input() {
    char (*row)[MAP_SIZE] = map;
    while (!feof(stdin)) {
        scanf("%s", *row);
        for (char* cur = row[0]; *cur; ++cur) {
            *cur -= '0';
        }
        ++row;
    }
    height = row - map;
    while (map[0][width])
        ++width;
}

void swap(int i, int j) {
    heap[i].y ^= heap[j].y ^= heap[i].y ^= heap[j].y;
    heap[i].x ^= heap[j].x ^= heap[i].x ^= heap[j].x;
}

void push(int y, int x) {
    heap[heap_size] = {
        .y = y,
        .x = x,
    };
    for (int i = heap_size; i > 0; i >>= 1) {
        int parent = i >> 1;
        if (f[heap[parent].y][heap[parent].x] > f[y][x]) {
            swap(parent, i);
        } else {
            break;
        }
    }
    ++heap_size;
    in_heap[y][x] = true;
}

void pop(int* y, int* x) {
    *y = heap[0].y;
    *x = heap[0].x;
    // int min = 999999999;
    // for (int i = 0; i < heap_size; ++i) {
    //     if (min > f[heap[i].y][heap[i].x]) {
    //         min = f[heap[i].y][heap[i].x];
    //     }
    // }
    // TODO: SOMETIMES actual is less than top
    // printf("top/actual minscore: %d/%d\n", f[*y][*x], min);
    --heap_size;
    in_heap[*y][*x] = false;
    heap[0] = {
        .y = heap[heap_size].y,
        .x = heap[heap_size].x,
    };
    for (int i = 0; (i << 1) < heap_size;) {
        int j = i << 1;
        int right = (i << 1) + 1;
        if (right < heap_size && f[heap[right].y][heap[right].x] < f[heap[j].y][heap[j].x]) {
            j = right;
        }
        if (f[heap[i].y][heap[i].x] > f[heap[j].y][heap[j].x]) {
            swap(i, j);
            i = j;
        } else {
            break;
        }
    }
}

int main() {
    read_input();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            dist[y][x] = 999999999;
        }
    }
    dist[0][0] = 0;
    f[0][0] = (height - 1) + (width - 1);
    push(0, 0);
    while (heap_size > 0) {
        int vy, vx;
        pop(&vy, &vx);
        if (vy == height - 1 && vx == width - 1) {
            break;
        }
        in_closed[vy][vx] = true;
        for (int dir = 0; dir < 4; ++dir) {
            int dy = 0;
            int dx = 0;
            switch (dir) {
                case 0: {dx = 1;} break;
                case 1: {dy = 1;} break;
                case 2: {dx = -1;} break;
                case 3: {dy = -1;} break;
            }
            int ny = vy + dy;
            int nx = vx + dx;
            if (nx == -1 || ny == -1 || nx == width || ny == height) {
                continue;
            }
            int tentative_dist = dist[vy][vx] + map[ny][nx];
            if (in_closed[ny][nx] || tentative_dist >= dist[ny][nx]) {
                continue;
            }
            dist[ny][nx] = tentative_dist;
            f[ny][nx] = tentative_dist + ((height - 1) - ny) + ((width - 1) - nx);
            if (!in_heap[ny][nx]) {
                push(ny, nx);
            }
        }
    }
    printf("%d", dist[height - 1][width - 1]);
    return 0;
}
