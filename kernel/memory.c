#include "memory.h"
#include "util.h"

uint32_t mmap_length;
mmap_entry *mmap;

void init_mmap_info() {
    memory_copy(0x8000, &mmap_length, 4);
    mmap = 0x8004;
}