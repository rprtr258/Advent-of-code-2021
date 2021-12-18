#include <stdio.h>
#include "common.h"

u8 packet[MAX_PACKET_SIZE];
int packet_size = 0, offset = 0;
i64 versions_sum = 0;

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
