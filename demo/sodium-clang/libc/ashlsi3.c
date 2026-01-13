#include "stdint.h"

typedef union {
    struct {
       int16_t low;
       int16_t high;
    } part;
    int32_t all;
} dwords;

int32_t __ashlsi3(int32_t a, int b) {
    const int bits_in_word = sizeof(int) * 8;   //16 bits
    dwords input;
    dwords result;
    input.all = a;
    if (b & bits_in_word) /* bits_in_word <= b < bits_in_dword */ {
        result.part.low = 0;
        result.part.high = input.part.low << (b - bits_in_word);
    } else /* 0 <= b < bits_in_word */ {
        if (b == 0)
            return a;
        result.part.low = input.part.low << b;
        result.part.high =
        (input.part.high << b) | (input.part.low >> (bits_in_word - b));
    }
    return result.all;
}
