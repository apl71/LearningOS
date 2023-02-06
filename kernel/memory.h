#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdint.h>

// 主存布局表的长度
#define MLT_LENGTH 32

// 主存布局表项的结构体
typedef struct  {
    uint64_t base_address;
    uint64_t length;
    uint32_t type;
    uint32_t acpi3;
} __attribute__((packed)) memory_layout_entry;

// 定义主存布局表
memory_layout_entry memory_layout_table[MLT_LENGTH];

// 初始化主存布局
void init_memory_layout_table();

#endif