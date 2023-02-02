#include "../drivers/screen.h"
#include "interrupt.h"
#include "pic.h"
#include "const.h"

int kernel_main() {
    // clear screen and print banner
    clear_screen();
    print_string(os_hello_msg, WHITE_ON_BLACK);
    // 初始化IDT
    print_string(idt_init_msg, WHITE_ON_BLACK);
    idt_init();
    // 初始化PIC
    print_string(pic_init_msg, WHITE_ON_BLACK);
    pic_init();

    // 测试中断
    __asm__ volatile ("int $0x21");

    for(;;) {
        asm("hlt");
    }
}