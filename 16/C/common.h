typedef unsigned char u8;
typedef long long i64;

const i64 MAX_PACKET_SIZE = 1000;
const i64 MAX_I64 = 0x7FFFFFFFFFFFFFFF;
enum PacketType {
    SUM = 0,
    PRODUCT = 1,
    MINIMUM = 2,
    LITERAL = 4,
    MAXIMUM = 3,
    GREATER = 5,
    LESS = 6,
    EQUAL = 7,
};

void read_input();
int proceed(int bits_cnt);
