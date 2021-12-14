enum Direction {
    UP,
    DOWN,
    FORWARD,
};

struct Command {
    enum Direction dir;
    int value;
};

int read_command(struct Command* c);

