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

u8 packet[1000];
int packet_size = 0, offset = 0;

u8 bits_from_hex(char c) {
    return c - (c <= '9' ? '0' : 'A' - 10);
}

int proceed(int bits_cnt) {
    int res = 0;
    int first_byte = offset >> 3;
    int local_offset = offset & 0x7;
    if (first_byte == (offset + bits_cnt) >> 3) {
        offset += bits_cnt;
        return (packet[first_byte] >> (8 - local_offset - bits_cnt)) & ((1 << bits_cnt) - 1);
    }
    int begin_size = 8 - local_offset;
    res = packet[first_byte] & ((1 << begin_size) - 1);
    int byte, end_size;
    for (end_size = bits_cnt - begin_size, byte=first_byte + 1; end_size > 8; ++byte, end_size -= 8) {
        res = (res << 8) | packet[byte];
    }
    offset += bits_cnt;
    return (res << end_size) | (packet[byte] >> (8 - end_size));
}

i64 binary_operator_packet(std::function<i64(i64, i64)> op, i64 init) {
    i64 acc = init, tmp;
    if (proceed(1)) {
        for (int subpackets = proceed(11); subpackets > 0; --subpackets) {
            parse_packet(&tmp);
            acc = op(acc, tmp);
        }
    } else {
        int total_subpackets_length = proceed(15);
        while (total_subpackets_length > 0) {
            total_subpackets_length -= parse_packet(&tmp);
            acc = op(acc, tmp);
        }
    }
    return acc;
}

i64 comparison_operator_packet(std::function<i64(i64, i64)> op) {
    proceed(15 - 4 * proceed(1));
    i64 first, second;
    parse_packet(&first);
    parse_packet(&second);
    return op(first, second);
}

i64 parse_packet(i64* res) {
    int old_offset = offset;
    proceed(3);
    int type = proceed(3);
    switch (type) {
        ARIPH_CASE(SUM, a + b, 0);
        ARIPH_CASE(PRODUCT, a * b, 1);
        ARIPH_CASE(MINIMUM, a < b ? a : b, 0x7FFFFFFFFFFFFFFF);
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
    char buf[2000];
    scanf("%s", buf);
    char* cur = buf;
    int i = 0;
    while (*cur) {
        char next_digit = *(cur + 1);
        if (next_digit) {
            packet[i] = bits_from_hex(*cur) << 4 | bits_from_hex(next_digit);
            ++i;
            packet_size += 2;
            cur += 2;
        }
    }
    long long ans;
    parse_packet(&ans);
    printf("%I64d", ans);
    return 0;
}
