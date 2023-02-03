#include "memory.h"

uint32_t get_low_memory() {
    uint32_t result;
    __asm__("int $0x12" : "=a" (result));
    return result;
}