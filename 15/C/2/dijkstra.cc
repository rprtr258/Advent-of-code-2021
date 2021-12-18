#include <stdio.h>

const int MAP_SIZE = 101;

char map[MAP_SIZE][MAP_SIZE];
int real_height = 0, real_width = 0, virtual_height, virtual_width;
short dist[MAP_SIZE * 5][MAP_SIZE * 5];
struct HeapEntry {
    int y, x;
    short dist;
} heap[MAP_SIZE * MAP_SIZE * 25];
int heap_size = 0;

char virtual_map(int virtual_y, int virtual_x) {
    int real_y = virtual_y % real_height;
    int real_x = virtual_x % real_width;
    char delta = (virtual_y / real_height) + (virtual_x / real_width);
    return (map[real_y][real_x] - 1 + delta) % 9 + 1;
}

void read_input() {
    char (*row)[MAP_SIZE] = map;
    while (!feof(stdin)) {
        scanf("%s", *row);
        for (char* cur = row[0]; *cur; ++cur) {
            *cur -= '0';
        }
        ++row;
    }
    real_height = row - map;
    virtual_height = real_height * 5;
    while (map[0][real_width])
        ++real_width;
    virtual_width = real_width * 5;
}

void swap(int i, int j) {
    heap[i].y ^= heap[j].y ^= heap[i].y ^= heap[j].y;
    heap[i].x ^= heap[j].x ^= heap[i].x ^= heap[j].x;
    heap[i].dist ^= heap[j].dist ^= heap[i].dist ^= heap[j].dist;
}

void push(int y, int x, short d) {
    heap[heap_size] = {
        .y = y,
        .x = x,
        .dist = d,
    };
    for (int i = heap_size; i > 0; i >>= 1) {
        int parent = i >> 1;
        if (heap[parent].dist > d) {
            swap(parent, i);
        } else {
            break;
        }
    }
    ++heap_size;
}

void pop(HeapEntry *res) {
    res->y = heap[0].y;
    res->x = heap[0].x;
    res->dist = heap[0].dist;
    --heap_size;
    heap[0] = {
        .y = heap[heap_size].y,
        .x = heap[heap_size].x,
        .dist = heap[heap_size].dist,
    };
    for (int i = 0, p = 0 << 1; (i << 1) < heap_size; p = i << 1) {
        int j = p;
        int right = p + 1;
        if (right < heap_size && heap[right].dist < heap[j].dist) {
            j = right;
        }
        if (heap[i].dist > heap[j].dist) {
            swap(i, j);
            i = j;
        } else {
            break;
        }
    }
}

void update_cell(int ny, int nx, short cur_dist) {
    short tentative_dist = cur_dist + virtual_map(ny, nx);
    if (tentative_dist < dist[ny][nx]) {
        dist[ny][nx] = tentative_dist;
        push(ny, nx, tentative_dist);
    }
}

int main() {
    read_input();
    short* cur = (short*)&dist;
    short* end = cur + MAP_SIZE * MAP_SIZE * 25;
    for (; cur != end; ++cur) {
        *cur = 0x7FFF;
    }
    dist[0][0] = 0;
    push(0, 0, 0);
    while (heap_size > 0) {
        HeapEntry cur;
        pop(&cur);
        if (cur.y == virtual_height - 1 && cur.x == virtual_width - 1) {
            break;
        }
        if (cur.dist > dist[cur.y][cur.x]) {
            continue;
        }
        if (cur.x + 1 < virtual_width) {
            update_cell(cur.y, cur.x + 1, cur.dist);
        }
        if (cur.y + 1 < virtual_height) {
            update_cell(cur.y + 1, cur.x, cur.dist);
        }
        if (cur.x > 0) {
            update_cell(cur.y, cur.x - 1, cur.dist);
        }
        if (cur.y > 0) {
            update_cell(cur.y - 1, cur.x, cur.dist);
        }
    }
    printf("%d", dist[virtual_height - 1][virtual_width - 1]);
    return 0;
}
