#include <stdio.h>
#include "../common.h"

extern int offset;
extern i64 versions_sum;

int parse_packet() {
    int old_offset = offset;
    int version = proceed(3);
    versions_sum += version;
    int type = proceed(3);
    if (type == PacketType::LITERAL) {
        int literal = 0;
        int quartet;
        iter: {
            quartet = proceed(5);
            literal = (literal << 4) | (quartet & 0xF);
        } while (quartet & 0x10) {
            goto iter;
        }
    } else {
        int length_type_id = proceed(1);
        switch (length_type_id) {
            case 0: {
                int total_subpackets_length = proceed(15);
                while (total_subpackets_length > 0) {
                    total_subpackets_length -= parse_packet();
                }
            } break;
            case 1: {
                for (int subpackets_cnt = proceed(11); subpackets_cnt > 0; --subpackets_cnt) {
                    parse_packet();
                }
            } break;
        }
    }
    return offset - old_offset;
}

int main() {
    read_input();
    parse_packet();
    printf("%I64d", versions_sum);
    return 0;
}
