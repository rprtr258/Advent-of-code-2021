typedef unsigned char u8;
typedef long long i64;

const i64 I64_MAX = 0x7FFFFFFFFFFFFFFF;
const int MAX_ELEMENTS = 20;
const int MAX_TEMPLATE_SIZE = 20;

extern u8 polymer_template[MAX_TEMPLATE_SIZE];
extern u8 template_size;
extern int elements_size;
extern u8 pair[MAX_ELEMENTS][MAX_ELEMENTS];
extern i64 elements_count[MAX_ELEMENTS];

void read_input();
i64 calc_ans_by_elements_count();
i64 solve(int steps);
