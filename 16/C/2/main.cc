#include <stdio.h>
#include <functional>
#include "../common.h"
#define ARIPH_CASE(type, op, init) case PacketType::type: { \
    *res = binary_operator_packet([](i64 a, i64 b) {return op;}, init); \
} break;
#define COMPARE_CASE(type, op) case PacketType::type: { \
    *res = comparison_operator_packet([](i64 a, i64 b) {return a op b;}); \
} break;

extern int offset;

i64 parse_packet(i64* result);

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
