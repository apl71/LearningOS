#include "../drivers/screen.h"
#include "interrupt.h"
#include "pic.h"
#include "const.h"
#include "memory.h"

int kernel_main() {
    // clear screen and print banner
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
    print_string(low_mem_msg, WHITE_ON_BLACK);
    uint32_t low_memory = get_low_memory();
    print_int(low_memory, 10, WHITE_ON_BLACK);
    print_string(new_line, WHITE_ON_BLACK);

    for(;;) {
        asm("hlt");
    }
}