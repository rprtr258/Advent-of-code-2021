#include <stdio.h>
#include <string.h>
#include "common.h"

const int MAX_VERTICES = 20;

char v_names[MAX_VERTICES][6];
int v_size = 0;
int v_start, v_end;
int g[MAX_VERTICES][MAX_VERTICES];
int g_size[MAX_VERTICES];

int dfs(int v, const int visited_mask, bool was_one_cave_was_visited_twice) {
	if (v == v_end) {
		return 1;
    }
	int res = 0;
	for (int i = 0; i < g_size[v]; ++i) {
        int to = g[v][i];
        int to_mask = 1 << to;
		if (to == v_start || ((visited_mask & to_mask) && was_one_cave_was_visited_twice)) {
			continue;
        }
        bool is_small_cave = 'a' <= v_names[to][0] && v_names[to][0] <= 'z';
		if (is_small_cave) {
			if (visited_mask & to_mask) {
                res += dfs(to, visited_mask, true);
			} else {
                res += dfs(to, visited_mask | to_mask, was_one_cave_was_visited_twice);
            }
        } else {
            res += dfs(to, visited_mask, was_one_cave_was_visited_twice);
        }
    }
	return res;
}

int push_v(const char* v) {
    for (int i = 0; i < v_size; ++i) {
        if (strcmp(v_names[i], v) == 0) {
            return i;
        }
    }
    strcpy(v_names[v_size], v);
    return v_size++;
}

int solve(bool can_one_cave_be_visited_twice) {
    char buf[10];
    while (!feof(stdin)) {
        scanf("%s", buf);
        char* cur;
        for (cur = buf; *cur != '-'; ++cur)
            ;
        *cur = '\0';
        int v = push_v(buf);
        int w = push_v(cur + 1);
        g[v][g_size[v]++] = w;
        g[w][g_size[w]++] = v;
    }
    for (int i = 0; i < v_size; ++i) {
        if (strcmp(v_names[i], "start") == 0) {
            v_start = i;
        } else if (strcmp(v_names[i], "end") == 0) {
            v_end = i;
        }
    }
    return dfs(v_start, 0, !can_one_cave_be_visited_twice);
}
