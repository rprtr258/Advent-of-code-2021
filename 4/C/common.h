#include <functional>

typedef unsigned int u32;
typedef int matrix[5][5];

const u32 U32_MAX = 0xFFFFFFFF;

void sol(std::function<bool(u32, u32)> cmp);
