#include "memory.h"

void init_memory_layout_table() {
    __asm__ ("mov mlt, %%es:di" : "mlt" (&memory_layout_table));
    __asm__ ("xor %%ebx, %%ebx");
    __asm__ ("mov $0x534d4150, %%edx");
    __asm__ ("mov $0x0000e820, %%eax");
    __asm__ ("mov $0x00000018, %%ecx");
    __asm__ ("int $0x15");
}