#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#define UNREACHABLE return 0 // UNREACHABLE, DON'T YOU FUCKING WARNING AT ME
#define BOTH(i) for (int i = 0; i < 2; ++i)

Tree* make_node(Tree* left, Tree* right) {
    Tree* res = (Tree*)malloc(sizeof(Tree));
    res->tag = TreeTag::Node;
    res->content.child[0] = left;
    res->content.child[1] = right;
    res->content.parent = NULL;

    left->content.parent = res;
    right->content.parent = res;
    return res;
}

Tree* make_leaf(char value) {
    Tree* res = (Tree*)malloc(sizeof(Tree));
    res->tag = TreeTag::Leaf;
    res->content.value = value;
    return res;
}

Tree* copy(Tree* t) {
    switch (t->tag) {
        case TreeTag::Leaf: {
            return make_leaf(t->content.value);
        } break;
        case TreeTag::Node: {
            return make_node(copy(t->content.child[0]), copy(t->content.child[1]));
        } break;
    }
    UNREACHABLE;
}

Tree* read_tree_helper() {
    char cur = getchar();
    if (cur == '[') {
        Tree* left = read_tree_helper();
        getchar(); // ","
        Tree* right = read_tree_helper();
        getchar(); // "]"
        return make_node(left, right);
    } else {
        return make_leaf(cur - '0');
    }
}

Tree* read_tree() {
    Tree* res = read_tree_helper();
    getchar(); // "\n"
    return res;
}

void free_tree(Tree* t) {
    if (t->tag == TreeTag::Node) {
        BOTH(i) {
            free_tree(t->content.child[i]);
        }
    }
    free(t);
}

void push(Tree* start, char value, int dir) {
    Tree* cursor = start->content.parent;
    Tree* prev = start;
    while (cursor && cursor->content.child[dir] == prev) {
        prev = cursor;
        cursor = cursor->content.parent;
    }
    if (cursor) {
        cursor = cursor->content.child[dir];
        while (cursor->tag == TreeTag::Node) {
            cursor = cursor->content.child[1 - dir];
        }
        cursor->content.value += value;
    }
}

void explode(Tree* t, int depth = 1) {
    if (t->tag == TreeTag::Leaf) {
        return;
    } else if (depth == 4) {
        BOTH(i) {
            Tree* child = t->content.child[i];
            if (child->tag == TreeTag::Node) {
                BOTH(j) {
                    char value = child->content.child[j]->content.value;
                    push(child, value, j);
                }
                t->content.child[i] = make_leaf(0);
                free(child);
            }
        }
    } else {
        BOTH(i) {
            explode(t->content.child[i], depth + 1);
        }
    }
}

// returns true if did split
bool split(Tree* t) {
    if (t->tag == TreeTag::Leaf) {
        return false;
    }
    BOTH(i) {
        Tree* child = t->content.child[i];
        if (child->tag == TreeTag::Leaf) {
            if (child->content.value >= 10) {
                char left_value = child->content.value / 2;
                char right_value = child->content.value - left_value;
                t->content.child[i] = make_node(make_leaf(left_value), make_leaf(right_value));
                t->content.child[i]->content.parent = t;
                free_tree(child);
                return true;
            }
        } else if (split(t->content.child[i])) {
            return true;
        }
    }
    return false;
}

Tree* add(Tree* first, Tree* second) {
    Tree* res = make_node(first, second);
    iter: {
        explode(res);
    } while (split(res)) {
        goto iter;
    }
    return res;
}

int magnitude(Tree* t) {
    switch (t->tag) {
        case TreeTag::Leaf: {
            return t->content.value;
        } break;
        case TreeTag::Node: {
            return 3 * magnitude(t->content.child[0]) + 2 * magnitude(t->content.child[1]);
        } break;
    }
    UNREACHABLE;
}
