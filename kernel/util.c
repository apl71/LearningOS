#include "util.h"

void memory_copy(char *source, char *dest, int nbyte) {
    for (int i = 0; i < nbyte; ++i) {
        dest[i] = source[i];
    }
}

void memory_set(char *mem, char value, int length) {
    for (int i = 0; i < length; ++i) {
        mem[i] = value;
    }
}

int len_nums(int32_t num, int radix) {
    if (num == 0) {
        return 1;
    }
    int count = 0;
    while (num != 0) {
        count++;
        num /= radix;
    }
    return count;
}