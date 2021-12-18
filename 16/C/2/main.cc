#include <stdio.h>
#include <functional>
#define ARIPH_CASE(type, op, init) case PacketType::type: { \
    *res = binary_operator_packet([](i64 a, i64 b) {return op;}, init); \
} break;
#define COMPARE_CASE(type, op) case PacketType::type: { \
    *res = comparison_operator_packet([](i64 a, i64 b) {return a op b;}); \
} break;

typedef unsigned char u8;
typedef long long i64;

i64 parse_packet(i64* result);

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

u8 packet[MAX_PACKET_SIZE];
int packet_size = 0, offset = 0;

u8 bits_from_hex(char c) {
    return ('0' <= c && c <= '9' ? c - '0' : c - 'A' + 10);
}

void read_input() {
    char buf[MAX_PACKET_SIZE * 2];
    scanf("%s", buf);
    char* cur = buf;
    int i = 0;
    // I DOUBT HIGHLY ENOUGH TO ASSUME THERE ARE NO ODD EXAMPLES
    // BUT FUCKING TEXT DOESNT MENTION THIS
    while (*cur) {
        char next_digit = *(cur + 1);
        if (next_digit) {
            packet[i] = bits_from_hex(*cur) << 4 | bits_from_hex(next_digit);
            ++i;
            packet_size += 2;
            cur += 2;
        }
    }
}

int proceed(int bits_cnt) {
    int res = 0;
    int first_byte = offset / 8;
    int local_offset = offset % 8;
    if (first_byte == (offset + bits_cnt) / 8) { // result is in one byte
        // `first_byte` for e.g. offset=12, bits_cnt=3 layout is:
        // |A|A|A|A|B|B|B|C|
        // A is offset % 8 bits, B is bits_cnt bits, C is garbage
        u8 mask = (1 << bits_cnt) - 1;
        int garbage_size = 8 - local_offset - bits_cnt;
        res = (packet[first_byte] >> garbage_size) & mask;
    } else { // result is in several bytes
        // bytes for e.g. offset=12, bits_cnt=13 layout is:
        // <|A|A|A|A|B|B|B|B|> <|B|B|B|B|B|B|B|B|> <|B|C|C|C|C|C|C|C|>
//           ^_____^ ^_____^                         ^ ^___________^
//      local_offset begin_size               end_size garbage_size
        // A is offset % 8 bits, B is bits_cnt bits, C is garbage
        int begin_size = 8 - local_offset;
        u8 begin_mask = (1 << begin_size) - 1;
        res = packet[first_byte] & begin_mask;
        int byte, end_size;
        for (end_size = bits_cnt - begin_size, byte=first_byte + 1; end_size > 8; ++byte, end_size -= 8) {
            res = (res << 8) | packet[byte];
        }
        int garbage_size = 8 - end_size;
        res = (res << end_size) | (packet[byte] >> garbage_size);
    }
    offset += bits_cnt;
    return res;
}

i64 binary_operator_packet(std::function<i64(i64, i64)> op, i64 init) {
    i64 acc = init, tmp;
    int length_type_id = proceed(1);
    switch (length_type_id) {
        case 0: {
            int total_subpackets_length = proceed(15);
            while (total_subpackets_length > 0) {
                total_subpackets_length -= parse_packet(&tmp);
                acc = op(acc, tmp);
            }
        } break;
        case 1: {
            for (int subpackets = proceed(11); subpackets > 0; --subpackets) {
                parse_packet(&tmp);
                acc = op(acc, tmp);
            }
        } break;
    }
    return acc;
}

i64 comparison_operator_packet(std::function<i64(i64, i64)> op) {
    int length_type_id = proceed(1);
    switch (length_type_id) {
        case 0: {
            proceed(15);
        } break;
        case 1: {
            proceed(11);
        } break;
    }
    i64 first, second;
    parse_packet(&first);
    parse_packet(&second);
    return op(first, second);
}

// returns number of bits read while parsing
i64 parse_packet(i64* res) {
    int old_offset = offset;
    proceed(3); // skip version
    int type = proceed(3);
    switch (type) {
        ARIPH_CASE(SUM, a + b, 0);
        ARIPH_CASE(PRODUCT, a * b, 1);
        ARIPH_CASE(MINIMUM, a < b ? a : b, MAX_I64);
        ARIPH_CASE(MAXIMUM, a > b ? a : b, -1);
        case PacketType::LITERAL: {
            *res = 0;
            long long quartet;
            iter: {
                quartet = proceed(5);
                *res = (*res << 4) | (quartet & 0xF);
            } while (quartet & 0x10) {
                goto iter;
            }
        } break;
        COMPARE_CASE(GREATER, >);
        COMPARE_CASE(LESS, <);
        COMPARE_CASE(EQUAL, ==);
    }
    return offset - old_offset;
}

int main() {
    read_input();
    long long ans;
    parse_packet(&ans);
    printf("%I64d", ans);
    return 0;
}
