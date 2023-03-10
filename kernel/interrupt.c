#include "interrupt.h"
#include "pic.h"
#include "../drivers/screen.h"
#include "low_level.h"
#include "const.h"
#include "../drivers/keyboard.h"

void set_idt(int iv, ADDRESS_32 handler, uint8_t flag) {
    if (iv >= 255 || iv <= 0) {
        return;
    }
    idt[iv].isr_low    = LOW_16(handler);
    idt[iv].kernel_cs  = 0x08;                  // 代码段选择子
    idt[iv].reserved   = 0;
    idt[iv].attributes = flag;                  // P=1 DPL=00 0=0 D=1 Type=110
    idt[iv].isr_high   = HIGH_16(handler);
}

void idt_init() {
    // 初始化IDTR
    idtr.base  = (ADDRESS_32)idt;
    idtr.limit = IDT_MAX_DESCRIPTORS * sizeof(idt_entry_t) - 1;

    // 初始化异常部分
    print_string(MSG_EXCEPTION, WHITE_ON_BLACK);
    for (uint8_t vector = 0; vector < 32; ++vector) {
        set_idt(vector, (ADDRESS_32)isr_stub_table[vector], INTERRUPT_GATE);
    }
    print_string(MSG_OK, GREEN_ON_BLACK);

    // 注册33号中断向量（键盘中断），isr为keyboard_handler()
    print_string(MSG_SET_IDT_33, WHITE_ON_BLACK);
    set_idt(0x21, (ADDRESS_32)keyboard_handler, INTERRUPT_GATE);
    print_string(MSG_OK, GREEN_ON_BLACK);

    // 加载idtr
    print_string(MSG_LOAD_IDTR, WHITE_ON_BLACK);
    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");   // 启动中断
    print_string(MSG_OK, GREEN_ON_BLACK);
}

__attribute__((interrupt)) void keyboard_handler(struct interrupt_frame *frame) {
    uint8_t scancode = port_byte_in(0x60);
    print_scancode(scancode);

    pic_send_eoi(1);
}

void exception_handler() {
    __asm__ volatile ("cli; hlt");
}