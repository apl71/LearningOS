#include "../drivers/screen.h"
#include "interrupt.h"
#include "pic.h"

int main() {
    // clear screen and print banner
    clear_screen();
    char hello[] = "Welcome to my OS.\n";
    print_string(hello, GREEN_ON_BLACK);
    char idt_message[] = "Initializing IDT.\n";
    print_string(idt_message, GREEN_ON_BLACK);
    // 初始化IDT
    idt_init();

    // 测试中断
    __asm__ volatile ("int $0x21");

    for(;;) {
        asm("hlt");
    }
}