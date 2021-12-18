enum TreeTag {Leaf, Node};
struct Tree {
    TreeTag tag;
    union {
        struct {
            Tree* child[2];
            Tree* parent;
        };
        char value;
    } content;
};

Tree* read_tree();
Tree* copy(Tree* t);
void free_tree(Tree* t);
Tree* add(Tree* first, Tree* second);
int magnitude(Tree* t);
