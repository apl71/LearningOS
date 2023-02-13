#include "../drivers/screen.h"
#include "interrupt.h"
#include "pic.h"
#include "const.h"
#include "memory.h"

int kernel_main() {
    // 清空屏幕并打印欢迎语句
    clear_screen();
    print_string(MSG_HELLO_OS, WHITE_ON_BLACK);
    // 初始化PIC
    print_string(MSG_PIC_INIT, WHITE_ON_BLACK);
    pic_init();
    // 初始化IDT
    print_string(MSG_IDT_INIT, WHITE_ON_BLACK);
    idt_init();
    // 获取mmap
    init_mmap_info();
    // 打印主存信息
    print_string(MSG_MMAP_LENGTH, WHITE_ON_BLACK);
    print_int(mmap_length, 10, 0, WHITE_ON_BLACK);
    print_newline();
    print_string(MSG_MMAP_TITLE, WHITE_ON_BLACK);
    // 主存大小，单位为字节
    uint32_t memory_size = 0;
    for (int i = 0; i < mmap_length; ++i) {
        // 打印基地址
        print_string(MSG_HEX_HEADER, WHITE_ON_BLACK);
        print_uint(mmap[i].base_address, 16, 16, WHITE_ON_BLACK);
        print_string(MSG_BLANK, WHITE_ON_BLACK);
        // 打印长度
        print_string(MSG_HEX_HEADER, WHITE_ON_BLACK);
        print_uint(mmap[i].length, 16, 16, WHITE_ON_BLACK);
        print_string(MSG_BLANK, WHITE_ON_BLACK);
        // 打印类型
        switch (mmap[i].type) {
            case 1:  print_string(MSG_USABLE_MEM,   WHITE_ON_BLACK); break;
            case 2:  print_string(MSG_RESERVED_MEM, WHITE_ON_BLACK); break;
            case 3:  print_string(MSG_ACPI_RECLAIM, WHITE_ON_BLACK); break;
            case 4:  print_string(MSG_ACPI_NVS,     WHITE_ON_BLACK); break;
            case 5:  print_string(MSG_BAD_MEM,      WHITE_ON_BLACK); break;
            default: print_string(MSG_UNKNOWN_MEM,  WHITE_ON_BLACK); break;
        }
        // 打印apci支持
        if (mmap[i].acpi3 & 0x01 == 0x01) {
            print_string(MSG_ACPI_OK, WHITE_ON_BLACK);
        } else {
            print_string(MSG_ACPI_MISS, WHITE_ON_BLACK);
        }
        // 换行
        print_newline();
        // 统计可用主存空间
        if (mmap[i].type == 1 || mmap[i].type == 3) {
            memory_size += mmap[i].length;
        }
    }
    // 打印可用主存大小
    print_string(MSG_MEM_SIZE, WHITE_ON_BLACK);
    print_uint(memory_size, 10, 0, WHITE_ON_BLACK);
    print_string(MSG_NEWLINE, WHITE_ON_BLACK);
    
    for(;;) {
        __asm__ ("hlt");
    }
}