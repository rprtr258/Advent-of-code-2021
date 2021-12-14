#define X(x) (*x)[0]
#define Y(x) (*x)[1]
#define FOR_COORD(cur, begin, end) for (u16_2 *cur = begin; cur != end; ++cur)
#define FOR_EVERY_COORD(cur) FOR_COORD(cur, coords, coords_end)

typedef short u16_2[2];

extern u16_2 coords[];
extern u16_2* coords_end;
extern int coords_size;

void read_coords();
void read_folding();
