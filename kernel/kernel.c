#include "../drivers/screen.h"
#include "interrupt.h"
#include "pic.h"
#include "const.h"
#include "memory.h"

int kernel_main() {
    // 清空屏幕并打印欢迎语句
    clear_screen();
    print_string(os_hello_msg, WHITE_ON_BLACK);
    // 初始化PIC
    print_string(pic_init_msg, WHITE_ON_BLACK);
    pic_init();
    // 初始化IDT
    print_string(idt_init_msg, WHITE_ON_BLACK);
    idt_init();
    // 获取mmap
    init_mmap_info();
    // 打印主存信息
    print_string(mmap_length_msg, WHITE_ON_BLACK);
    print_int(mmap_length, 10, WHITE_ON_BLACK);
    
    for(;;) {
        __asm__ ("hlt");
    }
}