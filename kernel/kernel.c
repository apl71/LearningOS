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
    // 探测主存
    print_string(detect_mem_msg, WHITE_ON_BLACK);
    init_memory_layout_table();

    for(;;) {
        __asm__ ("hlt");
    }
}