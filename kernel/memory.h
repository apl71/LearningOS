#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>

// 主存布局表项的结构体
typedef struct  {
    uint64_t base_address;
    uint64_t length;
    uint32_t type;
    uint32_t acpi3;
} __attribute__((packed)) mmap_entry;

// mmap表项的长度
extern uint32_t mmap_length;
// 指向mmap表的指针
extern mmap_entry *mmap;

// 初始化mmap_length和mmap
void init_mmap_info();

#endif